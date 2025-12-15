#include "helper.h"

#include "texture.h"
#include "bvh.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "triangle.h"
#include "quadrilateral.h"
#include "constant_medium.h"
#include "mesh_loader.h"

void camera_1()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);

    world.add(make_shared<sphere>(
        point3(0, -1000, 0),
        1000,
        floor_mat));

    auto red_mat = make_shared<lambertian>(color(0.8, 0.1, 0.1));

    world.add(make_shared<sphere>(
        point3(0, 2, 0),
        1.0,
        red_mat));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;
    cam.background = color(0.7, 0.8, 1.0);

    cam.render(world);
}

void camera_2()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);

    world.add(make_shared<sphere>(
        point3(0, -1000, 0),
        1000,
        floor_mat));

    auto red_mat = make_shared<lambertian>(color(0.8, 0.1, 0.1));

    world.add(make_shared<sphere>(
        point3(0, 2, 0),
        1.0,
        red_mat));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(-6, 10, 3);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;
    cam.background = color(0.7, 0.8, 1.0);

    cam.render(world);
}

void camera_3()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    // Two spheres: one close, one far
    auto red = make_shared<lambertian>(color(0.8, 0.1, 0.1));
    auto blue = make_shared<lambertian>(color(0.1, 0.1, 0.8));

    world.add(make_shared<sphere>(point3(-1.5, 1, 0), 1.0, red));
    world.add(make_shared<sphere>(point3(1.5, 1, -4), 1.0, blue));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(0, 2, 5);
    cam.lookat = point3(0, 1, -2);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;
    cam.focus_dist = 5.0;
    cam.background = color(0.7, 0.8, 1.0);

    cam.render(world);
}

void camera_4()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    // Two spheres: one close, one far
    auto red = make_shared<lambertian>(color(0.8, 0.1, 0.1));
    auto blue = make_shared<lambertian>(color(0.1, 0.1, 0.8));

    world.add(make_shared<sphere>(point3(-1.5, 1, 0), 1.0, red));
    world.add(make_shared<sphere>(point3(1.5, 1, -4), 1.0, blue));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(0, 2, 5);
    cam.lookat = point3(0, 1, -2);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 1.0;
    cam.focus_dist = 4.0;
    cam.background = color(0.7, 0.8, 1.0);
    cam.render(world);
}

void antialiasing(int spp)
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);

    auto red = make_shared<lambertian>(color(0.9, 0.1, 0.1));
    world.add(make_shared<sphere>(
        point3(0, 2, 0),
        1.0,
        red));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = spp;
    cam.max_depth = 50;

    cam.vfov = 40;
    cam.lookfrom = point3(-2, 4, 2);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;
    cam.background = color(0.2, 0.4, 0.9);

    cam.render(world);
}

void purple_sphere()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);

    world.add(make_shared<sphere>(
        point3(0, -1000, 0),
        1000,
        floor_mat));

    auto purple = make_shared<lambertian>(color(0.5, 0.0, 0.5));

    world.add(make_shared<sphere>(point3(0, 1.0, 0), 1.0, purple));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);
    cam.lookfrom = point3(0, 2, 4);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 40;

    cam.render(world);
}

void checkered_sphere_and_triangle()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(
        0.2,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto checkered_mat = make_shared<lambertian>(checker);

    world.add(make_shared<sphere>(point3(-2, 0, 0), 1.0, checkered_mat));

    point3 v0(1, -1, 0);
    point3 v1(3, -1, 0);
    point3 v2(2, 1, 0);
    vec2 uv(0, 0);
    world.add(make_shared<triangle>(v0, v1, v2, uv, uv, uv, checkered_mat));

    // Ground
    auto ground = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);

    cam.lookfrom = point3(0, 2, 8);
    cam.lookat = point3(0.5, 0, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 30;

    cam.render(world);
}

void earth_sphere()
{
    hittable_list world;

    // Added a bright light to illuminate the environment
    auto sun = make_shared<diffuse_light>(color(20, 20, 20));
    world.add(make_shared<sphere>(point3(10, 10, 10), 3.0, sun));

    auto ambient_light = make_shared<diffuse_light>(color(0.2, 0.2, 0.2));
    world.add(make_shared<sphere>(point3(0, 0, 0), 1000, ambient_light));

    shared_ptr<texture> earth_tex;
    std::ifstream f("assets/earth.jpg");
    earth_tex = make_shared<image_texture>("assets/earth.jpg");
    std::cout << "Loaded earth texture\n";

    auto earth_mat = make_shared<lambertian>(earth_tex);
    world.add(make_shared<sphere>(point3(0, 0, 0), 2.0, earth_mat));

    for (int i = 0; i < 100; i++)
    {
        auto star_pos = point3::random(-50, 50);
        if (star_pos.length() > 20)
        {
            auto star = make_shared<diffuse_light>(color(1, 1, 1));
            world.add(make_shared<sphere>(star_pos, 0.1, star));
        }
    }

    camera cam;
    cam.aspect_ratio = 1.0;
    cam.image_width = 600;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;
    cam.background = color(0, 0, 0.05);
    cam.lookfrom = point3(0, 2, 8);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 30;
    cam.defocus_angle = 0.2;
    cam.focus_dist = 8.0;

    cam.render(world);
}

void perlin_sphere()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);

    world.add(make_shared<sphere>(
        point3(0, -1000, 0),
        1000,
        floor_mat));

    auto perlin_tex = make_shared<noise_texture>(4.0);
    auto perlin_mat = make_shared<lambertian>(perlin_tex);

    world.add(make_shared<sphere>(point3(0, 2.0, 0), 2.0, perlin_mat));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 600;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);
    cam.lookfrom = point3(0, 2, 8);
    cam.lookat = point3(0, 2, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 40;

    cam.render(world);
}

void perlin_cube()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);

    world.add(make_shared<sphere>(
        point3(0, -1000, 0),
        1000,
        floor_mat));

    auto perlin_tex = make_shared<noise_texture>(2.0);
    auto blue_perlin_mat = make_shared<lambertian>(perlin_tex);

    auto cube = load_obj_mesh("assets/cube.obj", blue_perlin_mat);

    if (cube)
    {
        cube = make_shared<rotate_y>(cube, 45);

        cube = make_shared<translate>(cube, vec3(0, 1.0, 0));

        world.add(cube);
    }

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);
    cam.lookfrom = point3(3, 3, 3);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 40;

    cam.render(world);
}

void specular()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(checker);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    auto mirror = make_shared<metal>(color(0.8, 0.8, 0.8), 0.0);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, mirror));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);
    cam.lookfrom = point3(4, 2, 4);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 20;

    cam.render(world);
}

void diffuse()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(checker);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    auto diffuse = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, diffuse));

    auto light = make_shared<diffuse_light>(color(15, 15, 15));
    world.add(make_shared<quadrilateral>(
        point3(-2, 5, -2),
        vec3(4, 0, 0),
        vec3(0, 0, 4),
        light));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.background = color(0, 0, 0);
    cam.lookfrom = point3(4, 2, 4);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 20;

    cam.render(world);
}

void dielectric_()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(checker);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    auto glass = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, glass));

    // Makes the sphere hollow, pretty cool effect
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.5, glass));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);
    cam.lookfrom = point3(4, 2, 4);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 20;

    cam.render(world);
}

void metal_()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(checker);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    auto gold = make_shared<metal>(color(0.8, 0.6, 0.2), 0.3);
    world.add(make_shared<sphere>(point3(-2, 1, 0), 1.0, gold));

    auto silver = make_shared<metal>(color(0.8, 0.8, 0.8), 0.05);
    world.add(make_shared<sphere>(point3(2, 1, 0), 1.0, silver));

    auto light = make_shared<diffuse_light>(color(4, 4, 4));
    world.add(make_shared<quadrilateral>(
        point3(-4, 5, -4),
        vec3(8, 0, 0),
        vec3(0, 0, 8),
        light));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 600;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);
    cam.lookfrom = point3(0, 3, 6);
    cam.lookat = point3(0, 1, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 25;

    cam.render(world);
}

void motion_blur_purple_sphere()
{
    hittable_list world;

    auto floor_tex = make_shared<checker_texture>(
        0.5,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_tex);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    auto purple = make_shared<lambertian>(color(0.5, 0.0, 0.5));

    point3 start_pos(0, 1.0, 0);
    point3 end_pos(0, 2.0, 0);

    world.add(make_shared<sphere>(start_pos, end_pos, 1.0, purple));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;
    cam.background = color(0.7, 0.8, 1);
    cam.lookfrom = point3(4, 2, 4);
    cam.lookat = point3(0, 1.5, 0);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 30;

    cam.render(world);
}

void cornell_box()
{
    hittable_list world;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    world.add(make_shared<quadrilateral>(point3(555, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), green));
    world.add(make_shared<quadrilateral>(point3(0, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), red));
    world.add(make_shared<quadrilateral>(point3(343, 554, 332), vec3(-130, 0, 0), vec3(0, 0, -105), light));
    world.add(make_shared<quadrilateral>(point3(0, 0, 0), vec3(555, 0, 0), vec3(0, 0, 555), white));
    world.add(make_shared<quadrilateral>(point3(555, 555, 555), vec3(-555, 0, 0), vec3(0, 0, -555), white));
    world.add(make_shared<quadrilateral>(point3(0, 0, 555), vec3(555, 0, 0), vec3(0, 555, 0), white));

    shared_ptr<hittable> box1 = box(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    world.add(box1);

    shared_ptr<hittable> box2 = box(point3(0, 0, 0), point3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));
    world.add(box2);

    camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 600;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;
    cam.background = color(0, 0, 0);

    cam.vfov = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat = point3(278, 278, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void cornell_smoke()
{
    hittable_list world;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    world.add(make_shared<quadrilateral>(point3(555, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), green));
    world.add(make_shared<quadrilateral>(point3(0, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), red));
    world.add(make_shared<quadrilateral>(point3(113, 554, 127), vec3(330, 0, 0), vec3(0, 0, 305), light));
    world.add(make_shared<quadrilateral>(point3(0, 555, 0), vec3(555, 0, 0), vec3(0, 0, 555), white));
    world.add(make_shared<quadrilateral>(point3(0, 0, 0), vec3(555, 0, 0), vec3(0, 0, 555), white));
    world.add(make_shared<quadrilateral>(point3(0, 0, 555), vec3(555, 0, 0), vec3(0, 555, 0), white));

    shared_ptr<hittable> box1 = box(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));

    shared_ptr<hittable> box2 = box(point3(0, 0, 0), point3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));

    world.add(make_shared<constant_medium>(box1, 0.01, color(0, 0, 0)));
    world.add(make_shared<constant_medium>(box2, 0.01, color(1, 1, 1)));

    camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 600;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;
    cam.background = color(0, 0, 0);

    cam.vfov = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat = point3(278, 278, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void final_scene()
{
    hittable_list world;

    auto floor_checker = make_shared<checker_texture>(
        0.8,
        color(0.2, 0.3, 0.1),
        color(0.9, 0.9, 0.9));
    auto floor_mat = make_shared<lambertian>(floor_checker);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, floor_mat));

    auto sphere_checker = make_shared<checker_texture>(
        0.2,
        color(0.8, 0.3, 0.1),
        color(0.1, 0.3, 0.8));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0,
                                  make_shared<lambertian>(sphere_checker)));

    world.add(make_shared<sphere>(point3(-2, 1, 0), 1.0,
                                  make_shared<metal>(color(0.8, 0.6, 0.2), 0.1)));

    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0,
                                  make_shared<dielectric>(1.5)));

    world.add(make_shared<sphere>(point3(2, 1, 0), 1.0,
                                  make_shared<metal>(color(0.8, 0.8, 0.8), 0.05)));

    auto motion_sphere = make_shared<lambertian>(color(0.5, 0.0, 0.5));
    world.add(make_shared<sphere>(
        point3(4, 1, -0.5),
        point3(4, 1, 0.5),
        1.0,
        motion_sphere));

    auto earth_tex = make_shared<image_texture>("assets/earth.jpg");
    auto earth_mat = make_shared<lambertian>(earth_tex);
    world.add(make_shared<sphere>(point3(-4, 1, 4), 1.0, earth_mat));

    auto perlin_tex = make_shared<noise_texture>(4.0);
    auto perlin_mat = make_shared<lambertian>(perlin_tex);
    world.add(make_shared<sphere>(point3(-2, 1, 4), 1.0, perlin_mat));

    auto cube_mat = make_shared<lambertian>(color(0.3, 0.7, 0.3));
    auto cube = load_obj_mesh("assets/cube.obj", cube_mat);
    if (cube)
    {
        cube = make_shared<translate>(cube, vec3(0, 1, 4));
        cube = make_shared<rotate_y>(cube, 45);
        world.add(cube);
    }

    auto boundary = make_shared<sphere>(point3(2, 1, 4), 1.5,
                                        make_shared<dielectric>(1.5));
    world.add(boundary);
    world.add(make_shared<constant_medium>(boundary, 0.2, color(0.8, 0.8, 0.9)));

    auto light1 = make_shared<diffuse_light>(color(4, 4, 4));
    world.add(make_shared<quadrilateral>(
        point3(-3, 5, -3),
        vec3(2, 0, 0),
        vec3(0, 0, 2),
        light1));

    auto light2 = make_shared<diffuse_light>(color(2, 2, 4));
    world.add(make_shared<quadrilateral>(
        point3(1, 5, 1),
        vec3(2, 0, 0),
        vec3(0, 0, 2),
        light2));

    auto tri_mat = make_shared<lambertian>(color(0.8, 0.2, 0.2));
    point3 v0(4, 0.5, 4);
    point3 v1(5, 0.5, 4);
    point3 v2(4.5, 1.5, 4);
    vec2 uv(0, 0);
    world.add(make_shared<triangle>(v0, v1, v2, uv, uv, uv, tri_mat));

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;
    cam.background = color(0.1, 0.1, 0.2);
    cam.lookfrom = point3(0, 5, 10);
    cam.lookat = point3(0, 1, 2);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 30;
    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render(world);
}

int main()
{
    switch (18)
    {
    case 1:
        camera_1();
        break;

    case 2:
        camera_2();
        break;

    case 3:
        antialiasing(1);
        break;

    case 4:
        antialiasing(100);
        break;

    case 5:
        purple_sphere();
        break;

    case 6:
        checkered_sphere_and_triangle();
        break;

    case 7:
        earth_sphere();
        break;

    case 8:
        perlin_sphere();
        break;

    case 9:
        final_scene();
        break;

    case 10:
        cornell_box();
        break;

    case 11:
        cornell_smoke();
        break;

    case 12:
        perlin_cube();
        break;

    case 13:
        specular();
        break;

    case 14:
        diffuse();
        break;

    case 15:
        dielectric_();
        break;

    case 16:
        metal_();
        break;

    case 17:
        motion_blur_purple_sphere();
        break;

    case 18:
        camera_3();
        break;

    case 19:
        camera_4();
        break;
    }
}