
-- INTRODUCTION --

GFXL is my work on graphics. It contains some linear algebra
classes and some GUI code which uses SDL. I intend to expand
this work, making more useful libraries designed for real-time
graphics programming and demos. My goal is a collection of
modular libraries, but much of this work dovetails which
working on a game engine.

This is all still experimental, so user beware. It is generally
safe, but imcomplete, and I have not yet switched over to an
actual unit testing system. I do test for bugs, but you never
know.

OVERVIEW

GFXL is an attempt to make a C++ friendly set of libraries that
uses OpenGL and SDL under the hood to work with creating pretty
pictures. While OpenGL and SDL already provide the raw
functionality for that task, there are still a little clunky.
They serve to smooth out the differences between systems, and
OpenGL in particular is still very much concerned with nitpicky
details that, while important, can distract from development
and learning to program for graphics. Neither library is a point
of entry for application code to start drawing things.

The first concern of GFXL is a core set of datatypes and utility
classes. In order to provide a generic set of bindings, OpenGL
thinks in terms of the lowest level abstractions possible and works
like a verbose C. In contrast, GLSL speaks directly in the
language of 3D graphics: linear algebra and multi-variate objects.
GFXL implements a suite of types that provide syntactic support
for these kinds of mathematical objects and deals with the details
of mapping them to OpenGL.

Component swizzling is among the most important functionality
provided in terms of ease of use, as is implemented as close as
possible to resemble a real feature of the language. The clarity
swizzling provides in expressing vector and matrix algorithms is
well worth the complexity. All primitive GLSL datatypes are
represented in the code with the same names, designed to map to
memory the way OpenGL and GLSL expect.

The utility classes implement safe and mindful ways of manipulating
those mathematical objects. A suite of mathematical operators is
provided which maintain accuracy and encapsulate the actual
calculations to make optimization easier. GFXL also has its own
type information system, used for debugging, testing, error
reporting, and integration with how OpenGL handles memory.

Wherever possible, the datatypes and support classes shift error
checking and catching firstly to preprocessing, then compilation,
then runtime exceptions. C++ does not have bounds or type checking
in certain compilation situations, and so some errors can only be
caught at runtime (dimension mismatches for arbitrary arrays are
an important instance of this).

The GUI related code is currently a wrapper for SDL 2.0 calls and
structures. This will change, and it is not complete yet as I have
not migrated the compilation settings from MinGW and Windows to GCC
and Linux.