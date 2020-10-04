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

#include "sphere.hpp"

#include "intersection_data.hpp"
#include "../scene/ray.hpp"
#include "lib/common/error_handling.hpp"

#include <cmath>

namespace cpe
{

sphere::sphere(vec3 const& center_param,float radius_param)
    :center_data(center_param),radius_data(radius_param)
{}

vec3 const& sphere::center() const
{
    return center_data;
}
float sphere::radius() const
{
    return radius_data;
}

bool sphere::intersect(ray const& ray_param,intersection_data& intersection) const
{

    vec3 const& u = ray_param.u();

    // ********************************************************** //
    // ********************************************************** //
    //  TO DO:
    //    Calcul d'intersection entre un rayon et une plan
    //
    // Variales:
    //  - Position initiale du rayon: ray_param.p0()
    //  - Vecteur directeur unitaire du rayon: u
    //  - Position du centre de la sphere: center_data
    //  - Rayon de la sphere: radius_data
    //
    // Aide de syntaxe:
    //  - Norme au carre d'un vecteur v: float norme=v.norm2();
    //             ou: float norme=v.dot(v);
    //
    // ********************************************************** //
    // ********************************************************** //

    //Le code suivant est arbitraire ett doit etre modifie
    vec3 const& p0 = ray_param.p0();
    // vec3 const& c0 = center_data;

    // a = dot(u,u);
    // b = 2*dot(u,p0-center_data);
    // c = dot(p0-center_data,p0-center_data)-pow(radius_data,2)

    float delta= 4.0f*pow(dot(p0-center_data,u),2) - 4.0f*dot(u,u)*(dot(p0-center_data,p0-center_data)-pow(radius_data,2));

    float t_inter ;

    if (delta<0)
    {
        return false;
    }

    if (delta==0)
    {
        t_inter = -(2*dot(u,p0-center_data))/(2*dot(u,u));
    }

    else
    {
        float t1 = ((-2*dot(u,p0-center_data) - sqrt(delta))/(2*dot(u,u)));
        float t2 = ((-2*dot(u,p0-center_data) + sqrt(delta))/(2*dot(u,u)));

        if (t1>=0 and t2>=0)
        {
            t_inter = fminf(t1,t2);
        }
        
        else if ( t1<0 && t2<0 )
        {
            return false;
        }
        
        else
        {
            t_inter = fmaxf(t1,t2);
        }
    }
    

    vec3 const& p_inter = ray_param.p0() + t_inter*u;

    vec3 const& n_inter = normalized(p_inter - center_data);

    intersection.set(p_inter,n_inter,t_inter);

    return true;


}
}
