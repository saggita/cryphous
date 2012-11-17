#include "colors.inc"
#include "shapes.inc"
#include "glass.inc"   
#include "skies.inc"

#declare posX = 0;
#declare posY = 0;
#declare posZ = 0; 
#declare Density = 0;

#declare Step = clock * 1000;
#declare Step = str(Step,-4,0)
#declare FileName = concat("particle",Step)
#declare FileName = concat(FileName,".txt")

#fopen file FileName read   

camera{
  location <0,40,-150>
  look_at <0,5,0>
  angle 30
}

light_source{ <50,30,-50> color White * 1.0 }

blob{
  threshold 0.05           
  #while( defined( file) )  
    #read( file, posX, posY, posZ, Density)
    sphere{<posX,posY,posZ>, 0.5, Density / 1000.0 }
  #end
  
  texture{
    pigment{rgbt<0,0,0.75, 0.9>} 
    finish{
        diffuse 0.6
        //reflection 0.01
        phong 0.4
        //specular 0.01
    }
  }
  //interior{ ior 1.03 }
}

/*object{
    Plane_XZ
    pigment{checker color Black, color White}
    translate < 0, -3, 0 >
    scale 40
}*/
sky_sphere{ S_Cloud5}        

#fclose file