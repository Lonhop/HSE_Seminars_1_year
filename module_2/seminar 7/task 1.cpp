#include <iostream>

class Particle {
public:
    struct Environment {
        double density;
        double friction;
    };
private:
    double x;
    double y;
    double vx;
    double vy;
    double mass;
    Environment env;
public:
    Particle(double x, double y, double mass, Environment env) : x(x), y(y), vx(0), vy(0), mass(mass), env(env) {}
    Particle(double mass) : Particle(0,0,mass,{1.0,0.1}) {}
    Particle& applyForce(double fx,double fy) {
        double ax = fx / this->mass;
        double ay = fy / this->mass;
        this->vx += ax;
        this->vy += ay;

        return *this;
    }
    Particle& tick(double dt) {
        double resistance = 1.0 - this->env.friction * dt;
        this->vx *= resistance;
        this->vy *= resistance;

        this->x += this->vx * dt;
        this->y += this->vy * dt;

        return *this;
    }
    void print() const {
        std::cout << "Particle: "
                  << "pos(" << this->x << ", " << this->y << ") "
                  << "vel(" << this->vx << ", " << this->vy << ") "
                  << "mass=" << this->mass << " "
                  << "env{density=" << this->env.density
                  << ", friction=" << this->env.friction << "}\n";
    }

};

int main() {
    Particle::Environment e{1.2, 0.05};
    Particle p(0, 0, 1.0, e);

    p.applyForce(10, 0).tick(0.1).tick(0.1);

    p.print();
    return 0;
}