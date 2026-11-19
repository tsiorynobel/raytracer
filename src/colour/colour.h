#pragma once

class Colour {
private:
    double _r;
    double _g;
    double _b;

public:
    Colour(double r, double g, double b);

    double r() const;
    double g() const;
    double b() const;

    Colour operator*(double t) const;
    // Part by part: how a light of one colour shows a surface of another.
    Colour operator*(const Colour& other) const;
};
