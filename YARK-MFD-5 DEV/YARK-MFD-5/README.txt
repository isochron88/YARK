----------------------------------------
YARK Yet Another Remote Kontroller
https://github.com/c4ooo/YARK/releases
----------------------------------------
Place the /YARK/ folder inside KSP's /GameData/ folder.
GameData/YARK/PluginData/YARK_PLUGIN/Config.xml contains configuration data.
Bindings folder contain an example showing how to communicate with plugin.
See https://forum.kerbalspaceprogram.com/index.php?/topic/176833-yet-another-remote-kontroller/

Build Yark Plugin
Visual Studio 2019

To fix Errors Like Below
D:\@Angie\YARKDEV\YARK-2 DEV\YARK-2\YARK_PLUGIN\AxisInput.cs(3,7,3,18): 
error CS0246: The type or namespace name 'UnityEngine' could not be found 
(are you missing a using directive or an assembly reference?)

From Menu Project->Add References->Browse.
Add these files from your kerbal Space Program Game
kerbal Space Program->KSP_x64_Data->Managed
Assembly-CSharp.dll
Assembly-CSharp-firstpass.dll
UnityEngine.dll
UnityEngine.CoreModule.dll
UnityEngine.UI.dll


Should Build successfully

YARK
Already in structure is Config.xml
DEPLOY/GameData/YARK/PluginData/YARK_PLUGIN/Config.xml contains configuration data.

Copy from YARK_PLUGIN/BIN/RELEASE/YARK_PLUGIN.dll
or 
YARK_PLUGIN/BIN/DEBUG/YARK_PLUGIN.dll
to
DEPLOY/GameData/YARK/YARK_PLUGIN.dll



-----------------------------

YARK-MFD
Get YARK for KSP here (required): https://github.com/c4ooo/YARK/releases
-----------------------------
https://forum.kerbalspaceprogram.com/index.php?/topic/177545-external-tcp-multi-function-display-kontroller/
https://github.com/c4ooo/YARK-MFD/releases
For 64-Bit windows.
Get YARK for KSP here (required): https://github.com/c4ooo/YARK/releases

Libraries
------------------------------
To build, the project requires the following libraries:

1) SDL2
==============
Simple DirectMedia Layer is a cross-platform development library designed to provide low level access 
to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D.

2) glew-2.0.0
==============
https://sourceforge.net/projects/glew/files/glew/2.0.0/
The OpenGL Extension Wrangler Library (GLEW) is a cross-platform C/C++ library that helps in 
querying and loading OpenGL extensions. GLEW provides efficient run-time mechanisms for determining 
which OpenGL extensions are supported on the target platform. All OpenGL extensions are exposed in 
a single header file, which is machine-generated from the official extension list. 
GLEW is available for a variety of operating systems, including Windows, Linux, Mac OS X, 
FreeBSD, IRIX, and Solaris. 

3) glm
==============
OpenGL  Mathematics  (GLM),  accessed  December  2017,  http://glm.g-truc.net/0.9.8/index.html
GLM is a C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) 
specification. GLM provides classes and basic math functions related to graphics concepts, 
such as vector, matrix, and quaternion. 


4) freetype
==============
https://github.com/ubawurinna/freetype-windows-binaries/tree/master/release%20dll/win64
FreeType is a popular software development library used to render text onto bitmaps, and provides 
support for other font-related operations. 

Visual Studio Properties
---------------
Look at properties->C/C++->General->Additional Include Directories
..\Lib\glm\;..\Lib\glew-2.0.0\include\;..\Lib\SDL2\include;..\Lib\freetype-2.7.1\include;

Linker Stuff

Look at properties->General->Additional Library Directories
..\Lib\freetype;..\Lib\glew-2.0.0\lib\Release\x64;..\Lib\SDL2\lib\x64
Look at properties->Linker->Input->Additional Dependencies
glu32.lib;SDL2.lib;freetype.lib;opengl32.lib;glew32s.lib;%(AdditionalDependencies)

OpenGL
------
https://www.khronos.org/registry/OpenGL-Refpages/
Good Introductory Lecture https://slideplayer.com/slide/7509267/


