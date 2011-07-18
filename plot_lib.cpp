#include "plot_lib.h"

Plotter::Plotter(){
  init();

}
  template <typename T>
Plotter::Plotter(std::vector<T> _data_x, std::vector<T> _data_y){
    data_x = _data_x;
    data_y = _data_y;
    init();
}
Plotter::Plotter(std::vector<std::string> &filenames){
  for(size_t i = 0; i < filenames.size() ; i++){
    std::string file = filenames[i];
    std::ifstream in;
    in.open(file.c_str());
    std::string line;
    while(getline(in, line)){
      read_line(line);
    }
  }
  init();
}

Plotter::~Plotter(){
   delete graph;
   delete canvas;
}

bool Plotter::init(){
  graph = new TGraph();
  canvas = new TCanvas("plot", "plot", 10, 10 , 1280,720);
  return true;
}


void Plotter::read_line(std::string line){
  std::string first,sec;
  std::string TR = line.c_str();
  std::replace(TR.begin(),TR.end(),',','\t');
  std::stringstream sstr(TR);
  sstr >> first >> sec;
  if(check(first) &&check(sec)){
    double _first = boost::lexical_cast<double>(first);
    double _sec = boost::lexical_cast<double>(sec);
    data_x.push_back(_first);
    data_y.push_back(_sec);
  }
}


bool Plotter::check(std::string a){
  try{
    double d = boost::lexical_cast<double>(a);
    (void)d;
    return true;
  }catch(boost::bad_lexical_cast){
    return false;
  }
}

bool Plotter::plot(bool autox , bool autoy){
  try{
    for(size_t i = 0; i < data_x.size(); i++){
      graph->SetPoint(i,data_x[i], data_y[i]);
    }
    
  if(!opt.autox){
    graph->GetHistogram()->GetXaxis()->SetRangeUser(opt.startx, opt.stopx);
  }
  
  
  if(!opt.autoy){
    graph->GetHistogram()->GetYaxis()->SetRangeUser(opt.starty, opt.stopy);
  }
  graph->GetHistogram()->SetXTitle(opt.xlabel.c_str());
  graph->GetHistogram()->SetYTitle(opt.ylabel.c_str());
  graph->SetTitle(opt.plot_name.c_str());
  graph->Draw("A*");
  }catch(std::runtime_error &e){
    std::cerr << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Plotter::save_image(std::string filename){
  try{
    TImage *img = TImage::Create();
    img->FromPad(canvas);
    img->WriteImage(filename.c_str());
    return true;
  }catch(std::runtime_error &e){
    std::cerr << e.what() << std::endl;
    return false;
  }
}

void Plotter::set_options(myoptions opt){
  this->opt = opt;
}
