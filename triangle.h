#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "aabb.h"
#include "hittable.h"
#include "helper.h"

class triangle : public hittable
{
public:
    // Stationary triangle
    triangle(const point3 &_v0, const point3 &_v1, const point3 &_v2,
             shared_ptr<material> m)
        : v0_moving(_v0, vec3(0, 0, 0), 0),
          v1_moving(_v1, vec3(0, 0, 0), 0),
          v2_moving(_v2, vec3(0, 0, 0), 0),
          mat(m)
    {
        bbox = aabb(_v0, _v1, _v2);
    }

    // Moving triangle (motion blur)
    triangle(const point3 &v0_start, const point3 &v1_start, const point3 &v2_start,
             const point3 &v0_end, const point3 &v1_end, const point3 &v2_end,
             shared_ptr<material> m)
        : v0_moving(v0_start, v0_end - v0_start, 0),
          v1_moving(v1_start, v1_end - v1_start, 0),
          v2_moving(v2_start, v2_end - v2_start, 0),
          mat(m)
    {
        // Evaluate vertices at time 0
        point3 a0 = v0_start;
        point3 b0 = v1_start;
        point3 c0 = v2_start;

        // Evaluate vertices at time 1
        point3 a1 = v0_end;
        point3 b1 = v1_end;
        point3 c1 = v2_end;

        // Two boxes: start-time triangle, end-time triangle
        aabb box_start(a0, b0, c0);
        aabb box_end(a1, b1, c1);

        // Final AABB must contain both
        bbox = aabb(box_start, box_end);
    }

    // Return bounding box for BVH
    aabb bounding_box() const override
    {
        return bbox;
    }

    virtual bool hit(const ray &r, interval t_range, hit_record &rec) const override
    {
        // Evaluate vertices at the ray's time
        point3 v0 = v0_moving.at(r.time());
        point3 v1 = v1_moving.at(r.time());
        point3 v2 = v2_moving.at(r.time());

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

private:
    ray v0_moving, v1_moving, v2_moving;
    shared_ptr<material> mat;
    aabb bbox;
};

#endif
