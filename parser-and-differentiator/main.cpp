#include "parser.cpp"
#include "visualize.cpp"
#include "simplify.cpp"
#include "differentiate.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

void createTex(const std::string text, const std::string filename) {
    std::ofstream fout(filename);
    assert(fout.is_open());

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

std::string readText(const std::string filename) {
    std::ifstream fin(filename);
    assert(fin.is_open());
    
    std::string text;
    fin >> text;
    return text;
}

int main(int argc, char** argv) {
    assert(argc == 3);
    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];
    outputFilename += ".tex";
    
    std::string text = readText(inputFilename);
    
    createTex(text, outputFilename);
    system((std::string("pdflatex ") + outputFilename).c_str());
}
