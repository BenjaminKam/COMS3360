#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "helper.h"

class triangle : public hittable
{
public:
    point3 v0, v1, v2;
    shared_ptr<material> mat;

    triangle(const point3 &_v0, const point3 &_v1, const point3 &_v2,
             shared_ptr<material> m)
        : v0(_v0), v1(_v1), v2(_v2), mat(m)
    {
    }

    virtual bool hit(const ray &r, interval t_range, hit_record &rec) const override
    {
        // Möller–Trumbore algorithm
        vec3 v0v1 = v1 - v0;
        vec3 v0v2 = v2 - v0;
        vec3 pvec = cross(r.direction(), v0v2);
        double det = dot(v0v1, pvec);

        if (fabs(det) < 1e-8)
            return false;
        double invDet = 1.0 / det;

        vec3 tvec = r.origin() - v0;
        double u = dot(tvec, pvec) * invDet;
        if (u < 0 || u > 1)
            return false;

        vec3 qvec = cross(tvec, v0v1);
        double v = dot(r.direction(), qvec) * invDet;
        if (v < 0 || u + v > 1)
            return false;

        double t = dot(v0v2, qvec) * invDet;
        if (!t_range.contains(t))
            return false;

        rec.t = t;
        rec.p = r.at(t);
        rec.normal = unit_vector(cross(v0v1, v0v2));
        rec.set_face_normal(r, rec.normal);
        rec.mat = mat;

        return true;
    }
};

#endif
