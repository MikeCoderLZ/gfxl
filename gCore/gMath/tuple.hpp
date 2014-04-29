#ifndef ARGS_H
#define ARGS_H

template< size_t N, typename T >
class args {
public:
    typedef T                       arg_type;
    
                                    args( arg_type a ) :
                                         n_args( N ),
                                         arg( a )
                                         { last = *this;
                                           rest = 0; };
                                         
    args&                           operator()( arg_type a )
                                        {   
                                            args< N-1, arg_type > new_arg(a);
                                            this->last.rest = new_arg;
                                            this->last = new_arg;
                                            return *this;
                                        }
        
    size_t                          n_args;
    arg_type const&                 arg;
    args< N-1, arg_type> const&     next() { return rest; }
private:
    arg_type&                       last;
    args< N-1, arg_type > const&  rest;
}

template< 1, typename T >
class args {
public:
    typedef T                       arg_type;
    
                                    args( arg_type a ) :
                                        n_args( 1 ),
                                        arg( a ) {};
    size_t                          n_args;
    arg_type const&                 arg;    
}

// args(4.0f)(3,5f)(-1.23f);

#endif