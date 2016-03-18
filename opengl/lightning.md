# Lightning

## GL_POSITION

If `[3] != 0`, x,y,z is the punctual position, and attenuation is calculated.

Otherwise, light is at infinity (like the sun, the source is a plane) and `x,y,z` is the incoming direction, and attenuation is ignored.

## Attenuation

TODO formulas.

## GL_LIGHTNING

## GL_COLOR_MATERIAL

## glColorMaterial

<http://stackoverflow.com/questions/8494942/why-does-my-color-go-away-when-i-enable-lighting-in-opengl>

<https://sjbaker.org/steve/omniv/opengl_lighting.html>

Summary:

- without `glEnable(GL_COLOR_MATERIAL)`, color is determined by `glMaterial*`
- otherwise, color is determined by `glColor*` (like when lightning is off) `sjbakr.org` recommends this. We use it most of the time.
