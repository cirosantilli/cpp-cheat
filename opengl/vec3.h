/*
simple 3d vector class so as not to create large dependencies
on simple tests

for anything serious, consider real math libs
*/

#include <cmath>

template <class T=float>
class Vec3{

    public:

        //TODO how? maybe impossible
        //const static Vec3<T> X;
        //const static Vec3<T> Y;
        //const static Vec3<T> Z;

        T x;
        T y;
        T z;

        Vec3()
        : x(0.), y(0.), z(0.)
        {
        }

        Vec3(T x, T y, T z)
        : x(x), y(y), z(z)
        {
        }

        Vec3(const Vec3<T>& v)
        : x(v.x), y(v.y), z(v.z)
        {
        }

        //vector sum
        Vec3<T> operator+(const Vec3<T>& otherv){ 
            return Vec3<T>( this->x + otherv.x, this->y + otherv.y, this->z + otherv.z);
        }

        //vector subtraction
        Vec3<T> operator-(const Vec3<T>& otherv){ 
            return Vec3<T>( this->x - otherv.x, this->y - otherv.y, this->z - otherv.z);
        }

        //multiplication by constant
        Vec3<T> operator*(T a){ 
            return Vec3<T>( this->x * a, this->y * a, this->z * a);
        }

        //division by constant
        Vec3<T> operator/(T a){ 
            return Vec3<T>( this->x / a, this->y / a, this->z / a);
        }

        //dot product
        T dot(const Vec3<T>& otherv){ 
            return this->x * otherv.x + this->y * otherv.y + this->z * otherv.z;
        }

        //returns the euclidean norm of this vector
        T norm(){ 
            return sqrt( this->dot(*this) );
        }
        
        //returns the taxi norm of this vector (largest absolute value of a corrdinate)
        T taxi_norm(){ 
            //return max(abs(x), abs(y), abs(z));
            return 0.0;
        }

        //returns a unit vector in the same direction as this vector
        T unit(){    
            return (*this) / this->norm();
        }

        //euclidean distance
        T eucl(const Vec3<T>& other){    
            return (*this - other).norm();
        }

        //get a string representation
        std::string str(){
            char out[64];
            sprintf(out, "%4.2f\n%4.2f\n%4.2f\n", x, y, z);
            return std::string(out);
        }

        void rotY(GLfloat angle){
            GLfloat oldx = x;
            GLfloat oldz = z;
            GLfloat sina = sin(angle);
            GLfloat cosa = cos(angle);
            x = oldx*cosa + oldz*sina;
            z = - oldx*sina + oldz*cosa;
        }

};

//const Vec3<T> Vec3::X = Vec3<T>(1.,0.,0.);
//const Vec3<T> Vec3::Y = Vec3<T>(0.,1.,0.);
//const Vec3<T> Vec3::Z = Vec3<T>(0.,0.,1.);
