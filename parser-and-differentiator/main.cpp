#include "parser.cpp"
#include "visualize.cpp"
#include "simplify.cpp"
#include "differentiate.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

void createTex(const std::string filename) {
    std::ofstream fout(filename);

    std::string text = "x^x+x*y+42*sin(cos(ln(-x)))-1+y^2+0+z+0^1";
    auto node = Parser(text).parse();
    auto derivativeX = differentiate(node, 'x');
    auto derivativeY = differentiate(node, 'y');
    
    fout << "\\documentclass[12pt]{article}" << std::endl;
    fout << "\\usepackage[utf8x]{inputenc}" << std::endl;
    fout << "\\usepackage[english,russian]{babel}" << std::endl;
    fout << "\\usepackage{cmap}" << std::endl;
    fout << std::endl;
    fout << "\\begin{document}" << std::endl;
    
    fout << "$$f(x, y) = " + treeToString(node) + "$$" << std::endl;
    fout << "$$f(x, y) = " + treeToString(simplify(node)) + "$$" << std::endl;
    
    fout << "$$f(x, y)'_x = " + treeToString(derivativeX) + "$$" << std::endl;
    fout << "$$f(x, y)'_x = " + treeToString(simplify(derivativeX)) + "$$" << std::endl;
    
    fout << "$$f(x, y)'_y = " + treeToString(derivativeY) + "$$" << std::endl;
    fout << "$$f(x, y)'_y = " + treeToString(simplify(derivativeY)) + "$$" << std::endl;
    
    fout << "\\end{document}" << std::endl;
}

int main() {
    createTex("output.tex");
    system("pdflatex output.tex");
}
