#include  <stdio.h>
#include  <stdlib.h>
#include <sys/time.h>

// Define class Parent.

class Parent {
public:
    
    Parent () 
    { 
        printf("-> create parent: 0x%x\n", this); 
        p_parent = new int(0);
        printf("--- (parent) new int(0) 0x%x\n", p_parent);
    }
    ~Parent()
    {
        printf("--- (parent) delete int(0) 0x%x\n", p_parent);
        delete p_parent;
        printf("-< delete parent: 0x%x\n", this);
    }
    
    long long _getTime()
    {
        struct timeval t;
        struct timezone tz;
        
        gettimeofday(&t, &tz);
        return t.tv_usec + t.tv_sec * 1000000ULL;
    }
                               
private:
    int* p_parent;
};

// Define class Child.
class Child : public Parent {
public:
    Child() 
    {
        printf("--- -> create child: 0x%x\n", this); 
        p_child = new int(1); 
        printf("--- --- (child) new int(1) %x\n", p_child);
    }
    ~Child() 
    {
        printf("--- --- (child) delete int(1) %x\n", p_child); 
        delete p_child; 
        printf("--- -< detele child: 0x%x\n", this);
    }
private:
    int* p_child;
};

int main (void)
{
    // Lets allocate an object of class Child.
    Child* p_obj1 = new Child;
    
    p_obj1->_getTime();
    
    // Lets delete the object now. Since the pointer is of class 'Child*',
    // the destructor invoked is '~Child()' - which is what we expect to
    // occur. Ofcourse, after '~Child()' is invoked, the parent class's
    // destrcutor, '~Parent()' is also invoked - the compiler handles the
    // code to do that. Thus, both int pointed to by 'p_child' and the int
    // pointer to by 'p_parent' will be freed, in this order.
    delete p_obj1;
    
    
    // Now, lets allocate an object of class Child. Due to polymorphism rules,
    // we may store its pointer in a 'Parent*' pointer:
    Parent* p_obj2 = new Child;
    
    // Lets delete the object now. Because we are freed it via a pointer of
    // type 'Parent*', the compiler can not know that the object is in fact
    // a 'Child' object, and thus, will invoke the '~Parent()' destructor,
    // instead of invoking the '~Child()' destructor. The '~Child()' destructor
    // won't be invoked, and thus the int pointer to by 'p_child' will not
    // be deleted, and this memory will leak.
    
 //   delete p_obj2;
    
    int *p_i;
    
    for(int i = 0; i< 10; i++)
    {
        p_i = (int *)malloc(12*sizeof(int));
        printf("allocation: 0x%x\n", p_i);
        p_i[11] = 10;
        free(p_i);
    }

    
    p_obj2->_getTime();    
    delete p_obj2;
    
    printf("end of test\n");
}