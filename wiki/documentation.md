# Documentation

### Why do we need documentation?

* ___packaged communication___ with others:
    - developers wishing to ___understand___ and use our code
    - ___ourselves___ at a later point in time

### What are good documentation practices?

* ___annotate___ objects and nontrivial blocks
* keep the ___location___ close by the source
* use ___descriptive names___
* write ___self documenting___ (non-convoluted) code
* ___interfaces___ are documentation
* ... but add ___examples___
* don't write (and then rewrite) interface documentation too early during development
* writing strategic documentation early during development can be very useful
* link/forward to issue trackers and version control where applicable

### What do we expect from a documentation framework?

* extract useful ___info___
* ___augments___ self-documenting code (reuse the truth)
* diverse output ___formats___
* non-obtrusive syntax / application
* show ___dependencies___ (e.g. UML diagrams)
* integrate into (web) services / distribution
* pretty
* easy to configure and use
* fast

### Doxygen

In this course we will use [Doxygen](http://www.stack.nl/~dimitri/doxygen/).<br />
Check out the [CRTP-V(ege)table](exercise/vtable/doc) example (just execute `doxygen` in this
directory and look at `html/index.html`) for a quick demo.
Doxygen has a [comprehensive documentation](https://www.stack.nl/~dimitri/doxygen/manual/)
and a useful [commands overview](https://www.stack.nl/~dimitri/doxygen/manual/commands.html),
as well as [Markdown](https://daringfireball.net/projects/markdown/) support.
You can also download a [Doxygen Cheat Sheet](Cheatsheet_Doxygen.pdf)

#### Doxygen & CMake integration

We assume a general `CMakeLists.txt` in your project root and your source code
being in a directory called `src`.
Create a directory `doc` in the project root.

Insert `add_subdirectory(${PROJECT_SOURCE_DIR}/doc)` into your general CMakeLists.txt
and create `doc/CmakeLists.txt` with the following content:

    # add a target to generate API documentation with Doxygen
    find_package(Doxygen)
    option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

    if(BUILD_DOCUMENTATION)
        if(NOT DOXYGEN_FOUND)
            message(FATAL_ERROR "Doxygen is needed to build the documentation.")
        endif()

        set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        configure_file(${doxyfile_in} ${doxyfile} @ONLY)

        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
        )

        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
    endif()

Now run `doxygen -g doc/Doxyfile.in` and edit the variables in the
generated `doc/Doxyfile.in` as follows:

    PROJECT_NAME           = "@CMAKE_PROJECT_NAME@"
    PROJECT_NUMBER         = @VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@
    OUTPUT_DIRECTORY       = @PROJECT_SOURCE_DIR@/doc
    STRIP_FROM_PATH        = @PROJECT_SOURCE_DIR@ \
                             @PROJECT_BINARY_DIR@
    INPUT                  = @CMAKE_CURRENT_SOURCE_DIR@/../src/
    USE_MDFILE_AS_MAINPAGE = @doxy_main_page@
    GENERATE_LATEX         = NO

After this, your build correctly supports `make doc`, which will generate a `html`
directory in the `doc` of your project root (open `path_to_your_project/doc/html/index.html`
in a web browser). The `doc` in your build directory is only a temporary.


#### Read the Docs style

If you prefer the documentation style shown in the lecture (“Read the Docs” style),
you can apply it with the following modifications of the Doxyfile (or Doxyfile.in):

    HTML_HEADER            = @DOC_DIR@/include/header.html
    HTML_FOOTER            = @DOC_DIR@/include/footer.html
    HTML_EXTRA_STYLESHEET  = @DOC_DIR@/include/doxygen-extra.css
    DISABLE_INDEX          = YES
    GENERATE_TREEVIEW      = YES

The required `include/*` files can be copied from `lecture/exercise/pennaLV/doc/`

DOC_DIR has to be set in your `doc/CMakeLists.txt`:

    set(DOC_DIR ${PROJECT_SOURCE_DIR}/doc)  # needed in Doxyfile.in

### Sphinx
For python, we will use [Sphinx](http://sphinx-doc.org/) to generate the documantation.
Instead of using [Markdown](https://daringfireball.net/projects/markdown/)
it uses [reStructuredText](http://docutils.sourceforge.net/docs/ref/rst/restructuredtext.html)
as markup. We provide a small example in [here](tools/sphinx/doc).
The build process for the documentation is the following:

- make a doc folder and enter it
- call sphinx-quickstart and choose `yes` at the question `autodoc`
    - this will generate multiple files, also `conf.py`
- open the newly generated `conf.py` and import your source with
    - `sys.path.insert(0, os.path.abspath(`path_to_demo`))`
    - `import demo`
- to generate all .rts files automatically, we call:
    - `sphinx-apidoc path_to_demo -o path_to_doc`
- finally we run `make html` and have our documantation

#### Tweaks and Options

The `conf.py` file lets you specify many options. A few as example:

- Style: overwrite `html_theme` (see [html themes](http://sphinx-doc.org/theming.html) here)
    - for example `html_theme = 'sphinx_rtd_theme'`
- Documentation Order: `autodoc_member_order = "bysource"`

### Other documentation frameworks
**[Doc++](http://docpp.sourceforge.net/)**: generates documentation for C, C++, IDL and Java<br />
