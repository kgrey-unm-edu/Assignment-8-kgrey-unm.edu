#include <iostream>
#include <cmath>

using namespace std;

/********************************
        BASE CLASS
********************************/
class Field
{
protected:
    double *value;

public:
    // Default Constructor
    Field()
    {
        value = new double[3];

        value[0] = 0.0;
        value[1] = 0.0;
        value[2] = 0.0;
    }

    // Parameterized Constructor
    Field(double x, double y, double z)
    {
        value = new double[3];

        value[0] = x;
        value[1] = y;
        value[2] = z;
    }

    // Copy Constructor
    Field(const Field &other)
    {
        value = new double[3];

        value[0] = other.value[0];
        value[1] = other.value[1];
        value[2] = other.value[2];
    }

    // Destructor
    virtual ~Field()
    {
        delete[] value;
    }

    void printMagnitude()
    {
        cout << "("
             << value[0] << ", "
             << value[1] << ", "
             << value[2] << ")" << endl;
    }

    double magnitude()
    {
        return sqrt(
            value[0] * value[0] +
            value[1] * value[1] +
            value[2] * value[2]);
    }

    void setX(double x) { value[0] = x; }
    void setY(double y) { value[1] = y; }
    void setZ(double z) { value[2] = z; }

    double getX() const { return value[0]; }
    double getY() const { return value[1]; }
    double getZ() const { return value[2]; }
};

/********************************
      ELECTRIC FIELD CLASS
********************************/
class Electric_Field : public Field
{
private:
    double calculatedE;

public:
    Electric_Field() : Field()
    {
        calculatedE = 0.0;
    }

    Electric_Field(double x,
                   double y,
                   double z)
        : Field(x, y, z)
    {
        calculatedE = 0.0;
    }

    Electric_Field(const Electric_Field &other)
        : Field(other)
    {
        calculatedE = other.calculatedE;
    }

    void calculateElectricField(double Q,
                                double r)
    {
        const double epsilon0 = 8.854e-12;

        calculatedE =
            Q /
            (4.0 * M_PI *
             r * r *
             epsilon0);
    }

    double getCalculatedE()
    {
        return calculatedE;
    }

    // + Operator
    Electric_Field operator+(const Electric_Field &rhs)
    {
        Electric_Field temp;

        temp.value[0] =
            value[0] + rhs.value[0];

        temp.value[1] =
            value[1] + rhs.value[1];

        temp.value[2] =
            value[2] + rhs.value[2];

        return temp;
    }

    friend ostream &
    operator<<(ostream &out,
               const Electric_Field &e)
    {
        out << "("
            << e.value[0] << ", "
            << e.value[1] << ", "
            << e.value[2] << ")";

        return out;
    }
};

/********************************
      MAGNETIC FIELD CLASS
********************************/
class Magnetic_Field : public Field
{
private:
    double calculatedB;

public:
    Magnetic_Field() : Field()
    {
        calculatedB = 0.0;
    }

    Magnetic_Field(double x,
                   double y,
                   double z)
        : Field(x, y, z)
    {
        calculatedB = 0.0;
    }

    Magnetic_Field(const Magnetic_Field &other)
        : Field(other)
    {
        calculatedB = other.calculatedB;
    }

    void calculateMagneticField(double I,
                                double r)
    {
        const double mu0 =
            1.25663706e-6;

        calculatedB =
            (mu0 * I) /
            (2.0 * M_PI * r);
    }

    double getCalculatedB()
    {
        return calculatedB;
    }

    Magnetic_Field operator+(const Magnetic_Field &rhs)
    {
        Magnetic_Field temp;

        temp.value[0] =
            value[0] + rhs.value[0];

        temp.value[1] =
            value[1] + rhs.value[1];

        temp.value[2] =
            value[2] + rhs.value[2];

        return temp;
    }

    friend ostream &
    operator<<(ostream &out,
               const Magnetic_Field &b)
    {
        out << "("
            << b.value[0] << ", "
            << b.value[1] << ", "
            << b.value[2] << ")";

        return out;
    }
};

/********************************
             MAIN
********************************/
int main()
{
    cout << "=== ELECTRIC FIELD ===\n";

    Electric_Field E1(0, 1e5, 1e3);

    cout << "Components: ";
    E1.printMagnitude();

    cout << "Magnitude = "
         << E1.magnitude()
         << endl;

    E1.calculateElectricField(
        5e-6,
        0.2);

    cout << "Calculated Electric Field = "
         << E1.getCalculatedE()
         << " N/C"
         << endl;

    cout << "\n=== MAGNETIC FIELD ===\n";

    Magnetic_Field B1(2, 5, 8);

    cout << "Components: ";
    B1.printMagnitude();

    cout << "Magnitude = "
         << B1.magnitude()
         << endl;

    B1.calculateMagneticField(
        10.0,
        0.05);

    cout << "Calculated Magnetic Field = "
         << B1.getCalculatedB()
         << " Tesla"
         << endl;

    cout << "\n=== OPERATOR + ===\n";

    Electric_Field E2(1, 2, 3);
    Electric_Field E3(4, 5, 6);

    Electric_Field E4;

    E4 = E2 + E3;

    cout << "E2 = " << E2 << endl;
    cout << "E3 = " << E3 << endl;
    cout << "E4 = E2 + E3 = "
         << E4 << endl;

    cout << "\n";

    Magnetic_Field B2(1, 1, 1);
    Magnetic_Field B3(2, 2, 2);

    Magnetic_Field B4;

    B4 = B2 + B3;

    cout << "B2 = " << B2 << endl;
    cout << "B3 = " << B3 << endl;
    cout << "B4 = B2 + B3 = "
         << B4 << endl;

    return 0;
}
