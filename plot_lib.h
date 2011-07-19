#ifndef _PLOT_LIB_H
#define _PLOT_LIB_H

#include "pref.h"

/**
 * \brief  options for plot
 * Options for plotting, also the parameternames for the batch file
 */
struct myoptions{
public:
  double startx;
  double stopx;
  double starty;
  double stopy;
  bool autox;
  bool autoy;
  std::string plot_name;
  std::string xlabel;
  std::string ylabel;

myoptions() : startx(0),  stopx(200),
    starty(-300), stopy(0), autox(true),autoy(true), plot_name("plot"),
    xlabel("x"), ylabel("y"){
}
};


/**
 * \brief Plotter class
 * Plotter class that handels all the plotting an ROOT stuff
 */
class Plotter {
 public:
  Plotter();
  template <typename T>
  Plotter(std::vector<T> _data_x, std::vector<T> _data_y);
  Plotter(std::vector<std::string> &filenames);
  ~Plotter();
  bool plot(bool autox = true, bool autoy = true);
  bool save_image(std::string filename);
  void set_options(myoptions opt);
 private:
  std::vector<double> data_x;
  std::vector<double> data_y;
  std::vector<boost::shared_ptr<TGraph> > graph;
  TCanvas *canvas;
  void read_line(std::string line);
  bool check(std::string a);
  bool init();
  myoptions opt;
};









#endif
