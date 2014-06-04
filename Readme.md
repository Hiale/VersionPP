Version++
=========

What is Version++?
------------------

Version++ can be used to automatically create version information in C++ applications.

How does it work?
-----------------

It alters a header file before compiling. After you created a header file (see below), execute this application
with the header file to update it.

Example:
VersionPP.exe "C:\dev\proj\version.h"

How can I use it?
-----------------

Option A
1. Add VersionInfo.rc from the Template directory to your project.
2. Change CompanyName, FileDescription, LegalCopyright, ProductName to your needs.
3. Add VersionNo.h to your project.
3. Change the variable(s) in VersionNo.h accordantly. (see below)

Option B 
1. Add a new Resource to the project, select Version in the dialog.
2. Open the newly created file in text view (View Code).
3. Replace several values to variables:
Search for FILEVERSION, replace the value nearby by FILE_VERSION
Search for PRODUCTVERSION, replace the value nearby by PRODUCT_VERSION
Search for VALUE "FileVersion", replace the value nearby by FILE_VERSION_STRING
Search for VALUE "ProductVersion", replace the value nearby by PRODUCT_VERSION_STRING

The lines should look like this:
FILEVERSION FILE_VERSION
PRODUCTVERSION PRODUCT_VERSION
VALUE "FileVersion", FILE_VERSION_STRING
VALUE "ProductVersion", PRODUCT_VERSION_STRING

4. Add #include "VersionNo.h" (or any other header file name) on top of the file.
5. Add a new header file to your project. Name it like in step 4.
6. Copy the content from VersionNo.h in the template directory to your new file.
7. Change the variable(s) in accordantly. (see below)

How to use the header file?
---------------------------

In the header are one or two variables which need to changed. Either:
// ProductVersion 1.0.*.+
// FileVersion 1.0.*.+
OR
// Version 1.0.*.+

The first option can set different versions to the product and the file value, where the second sets both to the same value. If you don't mind, use option two.

What does 1.0.*.+ mean?
-----------------------

A version number contains four parts. Major, minor, build and revision. In this example major is 1, minor is 0, build is * and revision is +.
* and + are place holder symbols. They are used to set the number dynamically (see below).

Which place holder symbols can be used?
---------------------------------------
*
Like .NET assemblies, version information can automatically be generated. A * is supported in the build or the revision part only.
The algorithm works like this:
Build: Days since January 1st 2000.
Revision: Seconds since midnight divided by two.

+
Increases the value by one each time the application gets executed. Resets the value to zero when a part before resets.

^
Same as +, but it does not reset.

How to build
------------

1. Open the solution in Visual Studio 2013, other C++ 11 compilers might work as well.
2. Add boost (http://www.boost.org/) to your include directory. No need to compile the libraries, headers are sufficient.
3. The project should build.