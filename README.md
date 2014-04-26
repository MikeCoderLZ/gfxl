
-- INTRODUCTION --

GFXL is my work on graphics. I've got some linear algebra classes
as well as primitives and some GUI code, using SDL. I intend to
expand this work from time to time, making more useful libraries
designed for real-time graphics programming and demos. I'd like
to make some sort of engine, but who doesn't?

Use at your own risk; I test thoroughly for bugs, but I do not
guarantee this work is the best tool for the job and I have
implemented some esoteric things, like swizzling (don't get me
started; it was hard) and GLSL-like vector classes.

OVERVIEW

GFXL is an attempt to make a C++ application development friendly
set of libraries that uses OpenGL and SDL behind the scenes to
deal with creating pretty pictures. OpenGL in particular is still
very much concerned with nitpicky details that, while important,
can distract from development. It is not a point of entry for
application code to start drawing things: it is really a tool
that allows higher level code to talk to graphics hardware.

The first concern of GFXL is a core of datatypes and support
classes. In order to provide a generic set of bindings, OpenGL
thinks in terms of the lowest level abstractions possible and works
like a verbose C*. In contrast, GLSL and less clearly HLSL speak
directly in the language of 3D graphics: linear algebra and multi-
variate objects.

GFXL implements a suite of types that provide syntactic support
for these kinds of mathematical objects and deals with the details
of mapping them to OpenGL. Component swizzling is among the most
important functionality provided in terms of ease of use,
supported with a somewhat complex system of classes and compilation
units to simulate a language feature where there is none. Its
clarity in expressing vector and matrix algorithms is well worth
the complexity. You will find that all primitive GLSL datatypes
are represented in the code with the same names, engineered to
map to memory the same way as GLSL expects.

The support classes implement safe and mindful ways of manipulating
those mathematical objects. A suite of mathematical operators is
provided which maintain accuracy and encapsulate the actual
calculations to make optimization easier. GFXL also has its own
type information system, used for debugging, testing, error
reporting, and integration with OpenGL's memory.

Wherever possible, the datatypes and support classes shift error
checking and catching firstly to preprocessing, then compilation,
then runtime exceptions. C++ does not have bounds or type checking
in certain compilation situations, and so some errors can only be
caught at runtime (dimension mismatches are an important instance
of this).



* Let it be known that C is still one of my favorites and I am in no
way claiming that C is inferior; in fact if you can't write in C
you probably haven't finished cooking your programming skills yet.