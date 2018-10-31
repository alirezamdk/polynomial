#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

class term
{
  public:
    double Coef;
    int Exp;
    term()
    {
        Exp = 0;
        Coef = 0;
    }
    void setTerm(double Z, int T)
    {
        Exp = T;
        Coef = Z;
    }
};

class polynomial
{
    friend ostream &operator<<(ostream &a, polynomial &b);
    friend istream &operator>>(istream &input, polynomial &b);

    friend polynomial operator+(polynomial a, polynomial b);
    friend polynomial operator-(polynomial a, polynomial b);
    friend polynomial operator*(polynomial a, polynomial b);
    friend polynomial operator/(polynomial a, polynomial b);
    friend polynomial operator%(polynomial a, polynomial b);

    int terms;
    term *termArray;

  public:
    polynomial()
    {
        terms = 0;
    }
    polynomial(int n)
    {
        terms = n;
        termArray = new term[terms];
    }

    /* functions */

    int Max_deg()
    {
        int Max;
        Max = termArray[0].Exp;
        for (int i = 0; i < terms; i++)
        {
            if (Max <= termArray[i].Exp)
                Max = termArray[i].Exp;
        }
        return Max;
    }

    void Calculat() //A function that collects the coefficients of sentences that are common
    {
        int i;
        int Max = Max_deg();
        int tedad = 0;
        int temp = 0;

        double fer[Max + 1];

        for (i = 0; i <= Max; i++)
            fer[i] = 0.0;

        for (i = 0; i < terms; i++)
        {
            fer[termArray[i].Exp] += termArray[i].Coef;
        }

        for (i = Max; i >= 0; i--)
        {
            if (fer[i] != 0)
            {
                termArray[temp++].setTerm(fer[i], i);
            }
        }

        for (i = 0; i < Max + 1; i++)
        {
            if (fer[i] != 0)
                tedad++;
        }
        terms = tedad;
    }

    void print_p()
    {
        //////////////////////////////////////////////////////////////////
        // 0x^0 + 1x^0 + 0x^1 + 1x^1 + nx^0 + 0x^m + 1x^k + wx^1 + zx^q //
        //   0      |      0      |      |      0     |      |      |   //
        //         --    ----------      |            |      |      |   //
        //         |     |     -----------            |      |      |   //
        //         |     |     |      -----------------      |      |   //
        //         |     |     |      |      -----------------      |   //
        //         |     |     |      |      |        ---------------   //
        //         |     |     |      |      |        |                 //
        // =>   + (1) + (x) + (n) + (x^k) + (wx) + (zx^q)               //
        //////////////////////////////////////////////////////////////////
        for (int i = 0; i < terms; i++)
        {
            if (termArray[i].Coef != 0)
            {
                cout << "+";
            }
            if (termArray[i].Coef == 1)
            {
                cout << " (";
                goto Z;
            }
            if (termArray[i].Coef == 0)
                goto E;
            if (termArray[i].Exp == 0)
            {
                cout << " (" << termArray[i].Coef << ") ";
                goto E;
            }
            cout << " (" << termArray[i].Coef;
        Z:;
            if (termArray[i].Exp == 0)
            {
                cout << "1) ";
                goto E;
            }
            if (termArray[i].Exp == 1)
            {
                cout << "x) ";
            }
            else
            {
                cout << "x^";
                cout << termArray[i].Exp << ") ";
            }
        E:;
        }
    }
    /* END functions */
};
/* END class */

polynomial operator+(polynomial a, polynomial b)
{
    polynomial t(a.terms + b.terms);
    int i, c = 0;

    for (i = 0; i < a.terms; i++)
    {
        t.termArray[i].setTerm(a.termArray[i].Coef, a.termArray[i].Exp);
    }

    for (i = a.terms; i < a.terms + b.terms; i++)
    {
        t.termArray[i].setTerm(b.termArray[c].Coef, b.termArray[c].Exp);
        c++;
    }

    t.Calculat();

    return t;
}

polynomial operator-(polynomial a, polynomial b)
{
    polynomial y(a.terms + b.terms);
    int i, c = 0;

    for (i = 0; i < a.terms; i++)
    {
        y.termArray[i].setTerm(a.termArray[i].Coef, a.termArray[i].Exp);
    }

    for (i = a.terms; i < a.terms + b.terms; i++)
    {
        y.termArray[i].setTerm(b.termArray[c].Coef * (-1.0), b.termArray[c].Exp);
        c += 1;
    }

    y.Calculat();

    return y;
}

polynomial operator*(polynomial a, polynomial b)
{
    polynomial z(a.terms * b.terms);
    int i, j, c = 0;

    for (i = 0; i < a.terms; i++)
    {
        for (j = 0; j < b.terms; j++)
        {
            z.termArray[c].setTerm(a.termArray[i].Coef * b.termArray[j].Coef, a.termArray[i].Exp + b.termArray[j].Exp);
            c++;
        }
    }

    z.Calculat();

    return z;
}

polynomial operator/(polynomial a, polynomial b)
{
    if (a.Max_deg() >= b.Max_deg())
    {
        int p = (b.Max_deg() == 0) ? (1) : (b.Max_deg());
        int num = a.Max_deg() / p;

        polynomial d(num + 1);
        polynomial q(1);
        int c = 0;

        do
        {
            a.Calculat();
            q.termArray[0].setTerm((double)a.termArray[0].Coef / b.termArray[0].Coef, a.Max_deg() - b.Max_deg());
            d.termArray[c].setTerm(q.termArray[0].Coef, q.termArray[0].Exp);
            c++;
            a = (a - (q * b));
        } while (a.Max_deg() > p);

        d.terms = c;
        return d;
    }
    else
        return a;
}

polynomial operator%(polynomial a, polynomial b)
{
    ///////////////////////////////////////////////////////////////////////////////
    //  a(x) = Ax^n + ...       | b(x) = Bx^m + ...         Deg A >= deg B       //
    //  -( q[i++] * b(x))       |__________________________                      //
    //  ______________________    q(x) = ( A / B )x^n - m                        //
    //                                                                           //
    //  a(x) = a(x) -( q[i++] * b(x))   if deg a(x) < deg b(x) then a(x) = r(x)  //
    ///////////////////////////////////////////////////////////////////////////////
    int p = (b.Max_deg() == 0) ? (1) : (b.Max_deg());
    if (a.Max_deg() >= b.Max_deg())
    {
        polynomial q(1);

        do
        {
            q.termArray[0].setTerm((double)a.termArray[0].Coef / b.termArray[0].Coef, a.Max_deg() - b.Max_deg());
            a = (a - (q * b));
        } while (a.Max_deg() > p);

        return a;
    }
    else
        return a;
}

ostream &operator<<(ostream &a, polynomial &b)
{
    for (int i = 0; i < b.terms; i++)
    {
        if (b.termArray[i].Coef != 0)
        {
            a << "+";
        }
        if (b.termArray[i].Coef == 1)
        {
            a << " (";
            goto Z;
        }
        if (b.termArray[i].Coef == 0)
            goto E;
        if (b.termArray[i].Exp == 0)
        {
            a << " (" << b.termArray[i].Coef << ") ";
            goto E;
        }
        a << " (" << b.termArray[i].Coef;
    Z:;
        if (b.termArray[i].Exp == 0)
        {
            a << "1) ";
            goto E;
        }
        if (b.termArray[i].Exp == 1)
        {
            a << "x) ";
        }
        else
        {
            a << "x^";
            a << b.termArray[i].Exp << ") ";
        }
    E:;
    }
    return a;
}

istream &operator>>(istream &input, polynomial &b)
{
    for (int i = 0; i < b.terms; i++)
    {
        cout << " --- " << i + 1 << " ---" << endl;
        cout << " Coefficient :\t";
        input >> b.termArray[i].Coef;
        cout << " Exponent :\t";
        input >> b.termArray[i].Exp;
        if (b.termArray[i].Exp < 0)
        {
            cout << "Erorr: Exp < 0, Enter again .. " << endl;
            i--;
        }
        cout << endl;
    }
    return input;
}
