# Programming Style

### Why do we enforce programming styles?
* programs get read strictly* more often than they get written
* make it ___easy for others___ to read our code
* keep low blood pressure while ___reading other___ people's code

\* usually

### What do we expect from programming style conventions?
* ___consistency___: no rule changes
* ___readability___: prevent confusion
* make it easy to ___always follow___ the style guide
* efficient ___overview___ when skimming the code
* ___complete___ enough to prevent debates
* help to ___avoid___ introducing ___errors___

## Style Guides
In general, a project should stick to one style guide. This can be a custom one
(as is the case in many large projects and organisations), or one of the well
known documents:<br />
<br />
[Google Style Guide](https://google.github.io/styleguide/cppguide.html)<br />
[Mozilla Coding Style](https://developer.mozilla.org/en-US/docs/Mozilla/Developer_guide/Coding_Style)<br />
[GSS C++ Programming Style Guidelines](http://geosoft.no/development/cppstyle.html)<br />
[Boost Library Requirements and Guidelines](http://www.boost.org/development/requirements.html)<br />
<br />
[Indent Style Overview](https://en.wikipedia.org/wiki/Indent_style)



## Tools

We can use tools to apply coding styles to projects. The following programs
support globbing (*.txt), custom style specifications and can be integrated into
most common programming editors. In addition, many IDEs have their own
internal/automatic formatters.

#### clang-format
A reformatter from the LLVM/clang project using clang as parser. Supports the
LLVM, Google, Chromium, Mozilla and WebKit styles:<br />
`clang-format input.cpp -style=webkit > output.cpp`<br />
Check the [documentation](http://clang.llvm.org/docs/ClangFormat.html) for more options (e.g. `-i` for file replacement).

#### Artistic Style
A beautifier supporting more than a dozen styles. To reformat all code files in
the current directory and all subdirectories (backs the old files up with a
".orig" extension), run:<br />
`astyle "*" --recursive`<br />
Check the [documentation](http://astyle.sourceforge.net/astyle.html) for more options.
