#include "QuaternionHelper.h"


class Quaternion{
    public:
        double a;
        double bi;
        double cj;
        double dk;

        Quaternion() {
            this->a = 0;
            this->bi = 0;
            this->cj = 0;
            this->dk = 0;
        }
        Quaternion(double a, double bi, double cj, double dk) {
            this->a = a;
            this->bi = bi;
            this->cj = cj;
            this->dk = dk;
        }
        Quaternion conj(){
            return Quaternion(this->a, -this->bi, -this->cj, -this->dk);
        }
        std::string output(){
            std::cout << "(" << this->a << ", " << this->bi << ", " << this->cj << ", " << this->dk << ")" << std::endl;
        }
        Quaternion toPoint(){
            if(!abs(this->a) < 0.01){
                throw std::invalid_argument("Cannot convert Quaternion to a Point. Real part is not 0");
            }
            return Point3D(this->bi, this->cj, this->dk);
        }
        Quaternion add(Quaternion q){ 
            return Quaternion(this->a + q.a, this->bi + q.bi, this->cj + q.cj, this->dk + q.dk);
        }
        Quaternion sub(Quaternion q){
            return Quaternion(this->a - q.a, this->bi - q.bi, this->cj - q.cj, this->dk - q.dk);
        }
        Quaternion mul(Quaternion q){
            return Quaternion(this->a * q.a - this->bi * q.bi - this->cj * q.cj - this->dk * q.dk,
                              this->a * q.bi + this->bi * q.a + this->cj * q.dk - this->dk * q.cj,
                              this->a * q.cj - this->bi * q.dk + this->cj * q.a + this->dk * q.bi,
                              this->a * q.dk + this->bi * q.cj - this->cj * q.bi + this->dk * q.a);
        }

};

class Point3D : public Quaternion{
    public:
        double bi;
        double cj;
        double dk;

        Point3D() : Quaternion(0, 0, 0, 0){

            this->bi;
            this->cj;
            this->dk;
        }

        Point3D():Quaternion(){
            this->bi = 0;
            this->cj = 0;
            this->dk = 0;
        }

        Point3D(double bi, double cj, double dk) : Quaternion(0, bi, cj, dk){
            this->bi = bi;
            this->cj = cj;
            this->dk = dk;
        }

        Point3D(Quaternion q) : Quaternion(q.a, q.bi, q.cj, q.dk){
            this->bi = q.bi;
            this->cj = q.cj;
            this->dk = q.dk;
        }

        Point3D transform(Quaternion q){
            Quaternion q_conj = q.conj();
            return Point3D(q_conj.mul(this->add(q.mul(q_conj))).toPoint());
        }


        Point3D add(Point3D p){
            return Point3D(this->bi + p.bi, this->cj + p.cj, this->dk + p.dk);
        }
        Point3D sub(Point3D p){
            return Point3D(this->bi - p.bi, this->cj - p.cj, this->dk - p.dk);
        }

        std::string output(){
            std::cout << "(" << this->bi << ", " << this->cj << ", " << this->dk << ")" << std::endl;
        }

};
