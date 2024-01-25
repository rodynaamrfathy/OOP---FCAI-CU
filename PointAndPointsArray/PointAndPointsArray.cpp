#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Point
{
private:
    int X, Y;
public:
    Point()
    {
        X=0; Y=0;
    }
    Point(int x, int y)
    {
        X = x; 
        Y = y;
    }
    void setPoint(int x, int y) 
    {
        X = x; 
        Y = y;
    }
    int getX() 
    {
        return X;
    }
    int getY()
    {
        return Y;
    }
    void print()
    {
        cout<< "( " << X << ", " << Y << " )";
    }
};

class PointsArray
{
private:
    Point **pointsarray;
    int rows, columns;
public:
    //constuctors
    //default
    PointsArray()
    {
        rows = 0;
        columns = 0;
        pointsarray = nullptr;
    }
    PointsArray(int r, int c);
    //copy constructor
    PointsArray(const PointsArray &newmatrix);
    //getters
    int getRows() const;
    int getColumns() const;
    //overloading
    friend istream& operator>>(istream &in, PointsArray &pa);
    friend ostream& operator<<(ostream &out, const PointsArray &pa);
    PointsArray& operator=(const PointsArray& newmatrix);
    PointsArray operator+(int x) const;
    //other methods on class
    void addColumn(int, Point*);
    void deleteColumn(int);
    void swapRows(int, int);
    void setpoint(int, int, Point);
    void printmatrix();
    //destructor
    ~PointsArray()
    {
        for (int i = 0; i < rows; i++)
        {
            delete []pointsarray[i];
        }
    }
};

PointsArray :: PointsArray(int r, int c)
{
    rows = r;
    columns = c;
    pointsarray = new Point*[rows];
    for (int i = 0; i < rows; i++)
    {
        pointsarray[i] = new Point[columns];
        for (int j = 0; j < columns; j++)
        { 
                pointsarray[i][j].setPoint(0, 0);
        }
    }
}
PointsArray :: PointsArray(const PointsArray &newmatrix)
{
    rows = newmatrix.rows;
    columns = newmatrix.columns;
    pointsarray = new Point*[rows];
    for (int i = 0; i < rows; i++)
    {
        pointsarray[i] = new Point[columns];
        for (int j = 0; j < columns; j++)
        {
            pointsarray[i][j].setPoint(newmatrix.pointsarray[i][j].getX(), newmatrix.pointsarray[i][j].getY());
        }
    }
}
int PointsArray :: getRows() const
{
    return rows;
}
int PointsArray :: getColumns() const
{
    return columns;
}
PointsArray& PointsArray::operator=(const PointsArray& newmatrix)
{
    if (this != &newmatrix)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] pointsarray[i];
        }
        delete[] pointsarray;
        rows = newmatrix.rows;
        columns = newmatrix.columns;

        pointsarray = new Point*[rows];
        for (int i = 0; i < rows; i++)
        {
            pointsarray[i] = new Point[columns];
            for (int j = 0; j < columns; j++)
            {
                pointsarray[i][j] = newmatrix.pointsarray[i][j];
            }
        }
    }
    return *this;
}
PointsArray PointsArray :: operator+(int x) const
{
    PointsArray temp(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            temp.pointsarray[i][j].setPoint(this->pointsarray[i][j].getX() + x, this->pointsarray[i][j].getY() + x);
        }
    }
    return temp;
}
void PointsArray :: addColumn(int toadd, Point* newcolumn)
{
    PointsArray temp(rows, columns + 1);

    if (toadd < 0)
    {
        cout << "Invalid index to add." << endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < toadd; j++)
        {
            temp.pointsarray[i][j].setPoint(this->pointsarray[i][j].getX(), this->pointsarray[i][j].getY());
        }
        temp.pointsarray[i][toadd].setPoint(newcolumn[i].getX(), newcolumn[i].getY());
        for (int j = (toadd + 1); j < columns; j++)
        {
        temp.pointsarray[i][j].setPoint(this->pointsarray[i][j].getX(), this->pointsarray[i][j].getY());
        }
    }
    *this = PointsArray(temp);
}
void PointsArray :: deleteColumn(int todelete)
{
    if (todelete < 0 || todelete >= columns)
    {
        cout << "Invalid index to delete." << endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = todelete; j < columns - 1; j++)
        {
            pointsarray[i][j] = pointsarray[i][j + 1];
        }
    }
    columns--;
}
void PointsArray :: swapRows(int r1,int r2)
{
    Point* temp = pointsarray[r2];
    pointsarray[r2] = pointsarray[r1];
    pointsarray[r1] = temp;
}
void PointsArray :: setpoint(int r,int c,Point p)
{
    pointsarray[r][c].setPoint(p.getX(), p.getY());
}
void PointsArray :: printmatrix()
{
    if (rows == 0 || columns == 0)
    {
        cout << "ZERO Matrix, please fill the matrix" << endl;
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        cout << "[ ";
        for (int j = 0; j < columns; j++)
        {
            cout<< "(" << pointsarray[i][j].getX() << "," << pointsarray[i][j].getY() << ")";
            if (j != columns - 1)
                cout << " , ";
            else
                cout << " ";
        }
        cout << "]" << endl;
    }
}
//operator over loading >>
istream& operator>>(istream &in, PointsArray &pa)
{
    int x, y;
    cout << "enter matrix elements:" <<endl;
    for (int i = 0; i < pa.getRows(); i++)
    {
        for (int j = 0; j < pa.getColumns(); j++)
        {
            cout<< "enter the element with index [" << i << "][" << j << "]" <<endl;
            cout<<"enter x & y for the point"<<endl;
            in >> x >> y;
            pa.pointsarray[i][j].setPoint(x, y);
        }
    }
    return in;
}
ostream& operator<<(ostream &out, const PointsArray &pa)
{
    out << "matrix:";
    for (int i = 0; i < pa.getRows(); i++)
    {
        out << endl << "[ ";
        for (int j = 0; j < pa.getColumns(); j++)
        {
            pa.pointsarray[i][j].print();
            if (j != pa.getColumns() - 1)
                cout << " , ";
            else
                cout << "";
        }
        out<< " ]";
    }
    out << endl;
    return out;
}

/*
* Main - Entry Point
*
* Return: O on (success)
*/
int main ()
{
    int input;
    string flagstr;
    bool flag = true;
    int r, c, rd, cd;
    int num;
    int indexc1, indexc2;
    int coldelete, coladd;
    Point *p;
    int x, y;
    int i;
    PointsArray arr1;
    
    cout <<"********************************************" << endl;
    cout <<"*                                          *" << endl;
    cout <<"*            WELCOME TO MY PROGRAM         *" << endl;
    cout <<"*                                          *" << endl;
    cout <<"********************************************" << endl;
    
    while (flag)
    {
        cout << "1- Initialize PointsArray\n"
         << "2- Copy PointsArray\n"
         << "3- Display Number of Rows\n"
         << "4- Display Number of Columns\n"
         << "5- Enter PointsArray Elements\n"
         << "6- Display PointsArray Elements\n"
         << "7- Add Integer to PointsArray\n"
         << "8- Swap Rows\n"
         << "9- Delete Column\n"
         << "10- Add Column\n"
         << "11- Print PointsArray as Matrix\n"
         << "12- Exit" << endl;
        cin>> input;
        if(input ==1)
        {
            cout<< "New matrix:" <<endl;
            cout<< "rows:";
            cin>> r;
            cout<< "columns:";
            cin>> c;
            arr1 = PointsArray(r, c);
            continue;
        }
        else if(input == 2)
        {
            PointsArray arr2(arr1);
            cout <<"the copied matrix:"<<endl;
            arr2.printmatrix();
            continue;
        }
        else if(input==3)
        {
            cout<< arr1.getRows() <<endl;
            continue;
        }
        else if(input==4)
        {
            cout<< arr1.getColumns() <<endl;
            continue;
        }
        else if(input == 5)
        {
            cin>> arr1;
            continue;
        }
        else if(input == 6)
        {
            cout<< arr1;
            continue;
        }   
        else if(input == 7)
        {
            cout<<"enter the number you want to add to the point of the matrix"<<endl;
            cin>> num;
            PointsArray afteradd = arr1 + num;
            cout<< "New matrix" <<endl;
            afteradd.printmatrix();
            continue;
        }
        else if(input == 8)
        {
            cout<< "enter the index of row you want to swap (between " << "0 & " << r - 1 << ")" <<endl;
            cin>> indexc1 >> indexc2;
            arr1.swapRows(indexc1,indexc2);
            cout << "after swaping:" <<endl;
            cout<< arr1;
            continue;
        }
        else if(input == 9)
        {
            cout<<"enter the coloum to delete (between " << "0 & " << r - 1 << ")" <<endl;
            cin>> coldelete;
            arr1.deleteColumn(coldelete);
            continue;
        }
        else if(input == 10)
        {
            cout<<"enter the coloum to add (between " << "0 & " << r << ")" <<endl;
            cin>> coladd;
            p = new Point[c];
            for (i = 0; i < c; i++)
            {
                cout<< "the point number"<< i + 1 << ":" <<endl; 
                cout << "x:";
                cin>> x;
                cout<< "y:";
                cin>> y;
                p[i].setPoint(x, y);
            }
            arr1.addColumn(coladd, p);
            delete[] p;
            cout<< "after adding a column" <<endl;
            arr1.printmatrix();
            continue;
        }
        else if(input == 11)
        {
            arr1.printmatrix();
            continue;
        }
        else if (input == 12)
        {
            cout <<"********************************************" << endl;
            cout <<"*                                          *" << endl;
            cout <<"*     THANK YOU FOR USING MY PROGRAM       *" << endl;
            cout <<"*                                          *" << endl;
            cout <<"********************************************" << endl;
            flag = false;
            continue;
        }
        else
        {
            cout <<"wrong input try again.";
            continue;
        }
    }
    return 0;
}
