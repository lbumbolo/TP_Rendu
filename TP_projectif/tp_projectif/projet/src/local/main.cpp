
/** TP 5ETI IMI- CPE Lyon - 2015-2016 */



#include "lib/common/error_handling.hpp"

#include "discrete/bresenham.hpp"
#include "discrete/line_discrete.hpp"
#include "discrete/line_interpolation_parameter.hpp"
#include "image/image.hpp"
#include "image/drawer.hpp"
#include "discrete/triangle_scanline.hpp"
#include "image/image_zbuffer.hpp"
#include "lib/mesh/mesh.hpp"
#include "lib/mesh/mesh_io.hpp"
#include "render_engine/render_engine.hpp"
#include "lib/3d/mat4.hpp"
#include "lib/3d/mat3.hpp"
#include "image/texture.hpp"

#include <iostream>
#include <fstream>
#include <cmath>



using namespace cpe;

int main(int argc,char *argv[])
{

    std::cout<<"***********************"<<std::endl;
    std::cout<<"run "<<argv[0]<<" with "<<argc-1<<" parameters ... \n"<<std::endl;


    try
    {
        //////////////////Colorer des segments
        int const Nx = 1000;
        int const Ny = 1000;

        image im(Nx,Ny);
        im.fill({1.0f,1.0f,1.0f});

        // // Change two pixels 
        // im(5,5) = color(1.0f,1.0f,0.0f);
        // im(20,10) = color(1.0f,0.0f,0.0f);

        // // create a line of pixels
        // for(int k=0;k<20;++k)
        //     im(10+k,5) = color(k/20.0f,0.0f,1.0f-k/20.0f);

        // // create a column of pixels
        // for(int k=0;k<15;++k)
        //     im(5,5+k) = color(k/15.0f,k/15.0f,k/15.0f);

        // //////////////////Colorer avec Line
        // // creation d’une ligne discrete
        // line_discrete line; 
        // // ajout d’une position
        // line.push_back(ivec2(4,5));
        // // autre methode d’ajout
        // line.push_back({5,6});
        // ivec2 const p(6,7);
        // // autre methode d’ajout
        // line.push_back(p);
        // // affichage du contenu de la ligne
        // std::cout<<line<<std::endl;
        
        // //premiere methode de parcours de la ligne
        // for(int k=0;k<line.size();++k)
        // std::cout<<line[k]<<" ";
        // std::cout<<std::endl;
        // //deuxieme methode de parcours de la ligne
        // for(ivec2 const& p : line)
        // std::cout<<p<<" ";
        // std::cout<<std::endl;

        // //////////////////Bresenham
        // line_discrete line;
        // bresenham({5,5},{12,9},line);
        // std::cout<<line<<std::endl;

        /**************** CADRAN
        draw_line(im,{10,10},{20,15},color(0.5f,0.5f,0.5f));

        draw_line(im,{10,10},{20,5},color(1.0f,0.0f,0.0f));

        draw_line(im,{10,10},{15,0},color(0.0f,1.0f,0.0f));

        draw_line(im,{10,10},{5,0},color(0.0f,0.0f,1.0f));

        draw_line(im,{10,10},{0,5},color(1.0f,1.0f,0.0f));

        draw_line(im,{10,10},{0,15},color(1.0f,0.0f,1.0f));

        draw_line(im,{10,10},{5,20},color(0.0f,1.0f,1.0f));

        draw_line(im,{10,10},{15,20},color(0.0f,0.0f,0.0f));
        */

        /**************** CADRAN DEGRADE
        draw_line(im,{10,10},{20,15},color(0.5f,0.5f,0.5f),color(1.0f,1.0f,1.0f));

        draw_line(im,{10,10},{20,5},color(1.0f,0.0f,0.0f),color(1.0f,1.0f,1.0f));

        draw_line(im,{10,10},{15,0},color(0.0f,1.0f,0.0f),color(1.0f,1.0f,1.0f));

        draw_line(im,{10,10},{5,0},color(0.0f,0.0f,1.0f),color(1.0f,1.0f,1.0f));

        draw_line(im,{10,10},{0,5},color(1.0f,1.0f,0.0f),color(1.0f,1.0f,1.0f));

        draw_line(im,{10,10},{0,15},color(1.0f,0.0f,1.0f),color(1.0f,1.0f,1.0f));

        draw_line(im,{10,10},{5,20},color(0.0f,1.0f,1.0f),color(1.0f,1.0f,1.0f));

        draw_line(im,{10,10},{15,20},color(0.0f,0.0f,0.0f),color(1.0f,1.0f,1.0f));
        */

        // draw_triangle_wireframe(im,{0,5},{10,20},{20,5},color(1.0f,0.0f,0.0f));

        /********* Question 20 **********/
        // draw_triangle_wireframe(im , {15,12},{2,17},{6,3} , {0,0,0});
        // auto scanline = triangle_scanline_factory({15,12},{2,17},{6,3} ,
        // 0.0f,1.0f,2.0f);
        // std::cout<<scanline<<std::endl;


        /********* Question 21 **********/
        // draw_triangle_wireframe(im , {15,12},{2,17},{6,3} , {0,0,0});
        // auto scanline = triangle_scanline_factory({15,12},{2,17},{6,3} ,
        // color(1,0,0),color(0,1,0),color(0,0,1));
        // std::cout<<scanline<<std::endl;

        // /********* Question 23 **********/
        // draw_triangle(im,{0,5},{10,20},{20,5},color(1.0f,0.0f,0.0f));


        // /********* Question 24 **********/
        // draw_triangle(im,{0,5},{10,20},{20,5},color(1.0f,0.0f,0.0f),color(0.0f,1.0f,0.0f),color(0.0f,0.0f,1.0f));

        image_zbuffer zbuf(Nx,Ny);
        zbuf.fill(1.0f);     

        // /********* Question 28 **********/
        // draw_point(im,zbuf,{25,25},0.5f,color(1.0f,0.0f,0.0f));

        // /********* Question 29 **********/
        // draw_line(im,{10,10},{50,50},color(0.0f,1.0f,0.0f),color(1.0f,0.0f,1.0f), zbuf , -1.0f , 1.0f);

        // // /********* Question 28 **********/
        // draw_triangle(im,zbuf,{90,50},{700,700},{50,900},color(1.0f,0.0f,1.0f),color(0.0f,1.0f,1.0f),color(1.0f,0.0f,1.0f),1.f,-1.f,1.f);
        // draw_triangle(im,zbuf,{300,700},{800,900},{900,0},color(1.0f,0.0f,0.0f),color(0.0f,1.0f,0.0f),color(0.0f,0.0f,1.0f),0.f,-1.f,1.f);

        // /********* Question 31 **********/
        mat4 modelview;
        mat4 view;
        mat4 projection;
        projection.set_projection_perspective(60.0f*M_PI/180.0f,1.0f,1.0f,20.0f);
        modelview.set_identity();
        view.set_identity();

        vec3 const& p0 = {90,50,1.0f};
        vec3 const& p1 = {700.f,700.f,-1.f};
        vec3 const& p2 = {50.f,900.f,1.f};

        vec3 const& n0 = -normalized(p0);
        vec3 const& n1 = -normalized(p1);
        vec3 const& n2 = -normalized(p2);


        render(im,zbuf,p0,p1,p2,
            color(1.0f,0.0f,0.0f),color(0.0f,1.0f,0.0f),color(0.0f,0.0f,1.0f),
            n0,n1,n2,modelview,view,projection);


        vec3 const& p01 = {300,700,0.1f};
        vec3 const& p11 = {800.f,900.f,-1.f};
        vec3 const& p21 = {900.f,0.f,1.f};

        vec3 const& n01 = -normalized(p0);
        vec3 const& n11 = -normalized(p1);
        vec3 const& n21 = -normalized(p2);


        render(im,zbuf,p01,p11,p21,
            color(1.0f,0.0f,1.0f),color(0.0f,1.0f,1.0f),color(1.0f,0.0f,1.0f),
            n01,n11,n21,modelview,view,projection);

        im.save("mon_image.ppm");


    }
    catch(cpe::exception_cpe const& e)
    {


        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"Exception found"<<std::endl;
        std::cout<<e.info()<<std::endl;
        std::cout<<"\nSaving backtrace in file backtrace_log.txt"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;


        std::ofstream back_file("backtrace_log.txt");
        back_file<<e.info()<<std::endl;
        back_file<<e.info_backtrace();
        back_file.close();

        exit(1);
    }


    std::cout<<"Exit Main"<<std::endl;

    return 0;
}
