#include "functions.h"

using namespace std;


int main(void)
{
    int n , m ;

    cout << " Enter terms of polynomial A : ";
    cin >> n ;
    polynomial A(n) ;
    cin >> A ;
    cout << " A = " ;
    A.Calculat();
    A.print_p() ;

    cout << endl ;
    cout << endl ;

    cout << " Enter terms of polynomial B : ";
    cin >> m ;
    polynomial B(m) ;
    cin >> B ;
    cout << " B = " ;
    B.Calculat();
    B.print_p() ;
     

    cout << endl ;
    cout << endl ;
    cout << " --------------------------------------------------" ;
    cout << endl ;

    cout << " A + B = " ;
    (A + B).print_p() ;
    

    cout << endl ;
    cout << endl ;    


    cout << " A - B = " ;
    (A - B).print_p() ; 


    cout << endl ;
    cout << endl ;


    cout << " A * B = " ;
    (A * B).print_p() ; 
    

    cout << endl ;
    cout << endl ;
    

    cout << " A / B = (" ;
    (A / B).print_p() ;
    cout << ") + (" ;
    (A % B).print_p() ;
    cout << ") / (" ;
    cout << B ; 
    cout << ") " ;


    cout << endl ;
    cout << endl ;


    system("pause");
    system("pause");
    system("pause");
    cout << "Goodbye :)" ; 
    system("pause");
    return 0;
}
