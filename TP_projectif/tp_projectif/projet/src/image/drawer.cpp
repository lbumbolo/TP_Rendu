/*
**    TP CPE Lyon
**    Copyright (C) 2015 Damien Rohmer
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "drawer.hpp"

#include "discrete/ivec2.hpp"
#include "discrete/line_discrete.hpp"
#include "discrete/line_interpolation_parameter.hpp"
#include "discrete/bresenham.hpp"
#include "discrete/triangle_scanline.hpp"
#include "image.hpp"
#include "image_zbuffer.hpp"
#include "color.hpp"
#include "lib/3d/vec2.hpp"
#include "texture.hpp"

namespace cpe
{


void draw_line(image& im,ivec2 const& p0,ivec2 const& p1,color const& c)
{
    int x0 = p0.x();
    int y0 = p0.y();
    int x1 = p1.x();
    int y1 = p1.y();

    line_discrete line;
    bresenham({x0,y0},{x1,y1},line);

    for(int k = 0;k<line.size();++k)
    {
        im(line[k])=c;
        std::cout<<line[k]<<std::endl;
    }

    /*************************************
    // Affichez une ligne sur l'image
    //
    // Completez une structure line_discrete a l'aide de
    //   l'algorithme de Bresenham entre p0 et p1.
    // Pour tous les pixel p du segment
    //   Affecter im(p) a la couleur c
    //
    */
}

void draw_line(image& im,ivec2 const& p0,ivec2 const& p1,color const& c0,color const& c1)
{

    int x0 = p0.x();
    int y0 = p0.y();
    int x1 = p1.x();
    int y1 = p1.y();

    line_discrete line;
    bresenham({x0,y0},{x1,y1},line);

    for(int k = 0;k<line.size();++k)
    {
        line_interpolation_parameter interpolation(line);
        im(line[k])=(1.0f-float(interpolation[k]))*c1+float(interpolation[k])*c0;
        std::cout<<line[k]<<std::endl;
    }

    /*************************************
    // Affichez une ligne de couleur variable entre p0 de couleur c0, et p1 de couleur c1
    //
    // Completez une structure line_discrete a l'aide de
    //   l'algorithme de Bresenham entre p0 et p1.
    // Construire une structure line_interpolation_parameter
    //   a partir de la ligne discrete
    //
    // Pour toute les pixels de la ligne a l'indice k
    //    p <- position a l'indice k
    //    alpha <- parametre d'interpolation a l'indice k
    //    Calculer couleur courante en fonction de alpha, c0, et c1
    //    Appliquer la couleur courante a im(p)
    //
    */
}


void draw_triangle_wireframe(image& im,
                   ivec2 const& p0,ivec2 const& p1,ivec2 const& p2,color const& c)
{

    draw_line(im,p0,p1,c);
    draw_line(im,p1,p2,c);
    draw_line(im,p2,p0,c);
}


void draw_triangle(image& im,
                   ivec2 const& p0,ivec2 const& p1,ivec2 const& p2,color const& c)
{
    draw_triangle_wireframe(im,p0,p1,p2,c);
    auto scanline = triangle_scanline_factory(p0,p1,p2,c,c,c);

    auto it = scanline.begin();
    auto it_end = scanline.end();
    for( ; it!=it_end ; ++it )
    {
        //int const x = it->first;

        auto const& left = it->second.left;
        auto const& right = it->second.right;

        ivec2 const& p_left = left.coordinate;
        ivec2 const& p_right = right.coordinate;

        color const& param_left = left.parameter;
        color const& param_right = right.parameter;

        draw_line(im,p_left,p_right,param_left,param_right);
    }

    /*************************************
    // TO DO
    /*************************************
    // Affichez un triangle plein de couleur uniforme
    //
    // Definir une structure scanline sur (p0,p1,p2).
    //   le parametere peut etre definit arbitrairement.
    //   (par exemple triangle_scanline_factory(p0,p1,p2 , c,c,c); )
    //
    // Pour toutes les valeurs y du scanline
    //   pa <- position a gauche
    //   pb <- position a droite
    //   Afficher segment entre pa et pb de couleur c
    //
    */


}

void draw_triangle(image& im,
                   ivec2 const& p0,ivec2 const& p1,ivec2 const& p2,
                   color const& c0,color const& c1,color const& c2)
{

    draw_line(im,p0,p1,c0,c1);
    draw_line(im,p1,p2,c1,c2);
    draw_line(im,p2,p0,c2,c0);

    auto scanline = triangle_scanline_factory(p0,p1,p2,c0,c1,c2);

    auto it = scanline.begin();
    auto it_end = scanline.end();
    for( ; it!=it_end ; ++it )
    {
        //int const x = it->first;

        auto const& left = it->second.left;
        auto const& right = it->second.right;

        ivec2 const& p_left = left.coordinate;
        ivec2 const& p_right = right.coordinate;

        color const& param_left = left.parameter;
        color const& param_right = right.parameter;

        draw_line(im,p_left,p_right,param_left,param_right);
    }

    /*************************************
    // TO DO
    /*************************************
    // Affichez un triangle plein de couleur uniforme
    //
    // Definir une structure scanline sur (p0,p1,p2).
    //   de parametre (c0,c1,c2)
    //
    // Pour toutes les valeurs y du scanline
    //   pa <- position a gauche
    //   pb <- position a droite
    //
    //   ca <- couleur a gauche
    //   cb <- couleur a droite
    //
    //   Afficher segment entre pa et pb
    //        avec couleur variant entre ca et cb
    //
    */

}


void draw_point(image& im,image_zbuffer& zbuffer,ivec2 const& p,float const z,color const& c)
{
    if(p.x()<0 || p.x()>=im.Nx())
        return ;
    if(p.y()<0 || p.y()>=im.Ny())
        return ;

    if(z>-1 && z<1 && z<zbuffer(p))
    {
        zbuffer(p)=z;
        im(p)=c;
    }

    /*************************************
    // TO DO
    /*************************************
    // Si z est compris dans [-1,1] et que z
    //   est plus faible que zbuffer(p)
    //  Alors mettre a jour la couleur et le zbuffer
    */
}

/******* Draw line pour un z variable avec zbuffer   **********/
void draw_line(image& im, image_zbuffer& zbuffer, ivec2 const& p0,ivec2 const& p1,color const& c0,color const& c1,float const z0, float const z1)
{

    int x0 = p0.x();
    int y0 = p0.y();
    int x1 = p1.x();
    int y1 = p1.y();
    color c;
    float z;

    // std::cout<<"p0: "<<p0<<"p1: "<<p1<<"\n"<<std::endl;

    line_discrete line;
    bresenham({x0,y0},{x1,y1},line);


    for(int k = 0;k<line.size();++k)
    {
        line_interpolation_parameter interpolation(line);
        c = (1.0f-float(interpolation[k]))*c0+float(interpolation[k])*c1;
        z = (1.0f-float(interpolation[k]))*z0+float(interpolation[k])*z1;
        draw_point(im,zbuffer,line[k],z,c);
    }


}





void draw_triangle(image& im,image_zbuffer& zbuffer,
                   ivec2 const& p0,ivec2 const& p1,ivec2 const& p2,
                   color const& c0,color const& c1,color const& c2,
                   float z0,float z1,float z2)
{


    draw_line(im,zbuffer,p0,p1,c0,c1,z0,z1);
    draw_line(im,zbuffer,p1,p2,c1,c2,z1,z2);
    draw_line(im,zbuffer,p2,p0,c2,c0,z2,z0);

    auto scanline_c = triangle_scanline_factory(p0,p1,p2,c0,c1,c2);
    auto scanline_z = triangle_scanline_factory(p0,p1,p2,z0,z1,z2);

    auto it = scanline_c.begin();
    auto it_z = scanline_z.begin();
    auto it_end = scanline_c.end();
    for( ; it!=it_end ; ++it )
    {
        //int const x = it->first;

        auto const& left_c = it->second.left;
        auto const& right_c = it->second.right;


        auto const& left_z = it_z->second.left;
        auto const& right_z = it_z->second.right;

        ivec2 const& p_left = left_c.coordinate;
        ivec2 const& p_right = right_c.coordinate;

        color const& param_left = left_c.parameter;
        color const& param_right = right_c.parameter;

        float z_left = left_z.parameter;
        float z_right = right_z.parameter;

        draw_line(im,zbuffer,p_left,p_right,param_left,param_right,z_left,z_right);

        ++it_z;
    }

    /*************************************
    // TO DO
    /*************************************
    // Construire scanline avec couleur
    // Construire scanline avec profondeur
    // Parcourir les deux scanline (utilisez les iterateurs)
    //   pa <- point gauche
    //   pb <- point droit
    //
    //   ca <- couleur a gauche
    //   cb <- couleur a droite
    //
    //   za <- profondeur a gauche
    //   zb <- profondeur a droite
    //
    //   affiche ligne entre pa et pb
    //     de couleur variant entre ca et cb
    //     de pronfondeur variant entre za et zb
    */

}




}
