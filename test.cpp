#include "test.h"



int main(int argc, char* argv[]){
  int found_options = 0;
  myoptions opt;
  bool single_mode = false;
  po::options_description desc("Allowed Options");
  desc.add_options()
    ("help,h", "Produce this help message")
    ("interactive,i","Runs the program in interactive mode.")
    ("version,v","Prints Version")
    ("single,s", "Plots each File seperatly")
    ("batch,b",po::value<std::string>(), "Reads an optionsfile")
    ;
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc,argv,desc),vm);
  po::notify(vm);


  if (vm.count("help")) {
    std::cout << desc<< std::endl;
    return 3;
  }
  
  if(vm.count("version")){
    std::cout << "easyplot Version " << VERSION << "\nusing ROOT Version "<< ROOT_VERSION << "\nusing BOOST Version "
	      << BOOST_VERSION << "\neverything in it's License (LGPL, GSL & GPL for ROOT and Boost Software License for Boost)"<< "\neasyplot itself is under the GPL" << std::endl;
    return 4;
  }

  if(vm.count("interactive")){
   opt= menu();
   found_options++;
  }
  if(vm.count("single")){
    single_mode = true;
    found_options++; 
  }

  if(vm.count("batch")){
    std::string bfn = vm["batch"].as<std::string>();

    opt = parse_batch(bfn, single_mode);
    found_options += 2;
  }
  
  std::vector<std::string> names;
  //std::cout << found_options << std::endl;
  for(int i = 1 + found_options; i < argc; i++){
    names.push_back(argv[i]);
  }
  

  if(single_mode){
    for(std::vector<std::string>::iterator i = names.begin();i!=names.end(); i++ ){
      std::string tmp = *i;
      std::vector<std::string> tmpname;
      tmpname.push_back(tmp);
      Plotter *mypl = new Plotter(tmpname);
      mypl->set_options(opt);
      mypl->plot();
      boost::filesystem::path p2(tmp);
      std::string file = p2.parent_path().string();
      file += p2.stem().string();
      file += "_plot.png";
      std::cout <<"plotting: "<< file << std::endl;
      mypl->save_image(file);
      delete mypl;
     
    }
    return 0;
  }
  
 
  Plotter *myplot = new Plotter(names);
 
  myplot->set_options(opt);
  myplot->plot();
  boost::filesystem::path p2(names[0]);
  std::string file = p2.parent_path().string();
  file += p2.stem().string();
  file += "_plot.png";
  std::cout <<"plotting: "<<  file << std::endl;
  myplot->save_image(file);
  return 0;
}


myoptions menu(){
  int choice = 0;
  myoptions tmpopt;
  do{
    std::cout <<
      "[1] Set X-Axis Range\n"<<
      "[2] Set Y-Axis Range\n"<<
      "[3] Set Outputfilename\n"<<
      "[4] Set X Label\n"<<
      "[5] Set Y Label\n"<<
      "[6] Plot and exit Menu\n";
    std::cin >> choice;
    if(choice == 6) break;
    switch(choice){
    case 1:
      std::cout << "Please enter X-Axis Minimum: ";
      std::cin >>  tmpopt.startx;
      std::cout << "Please enter X-Axis Maximum: ";
      std::cin >>tmpopt.stopx;
      tmpopt.autox = false;
    break;
    case 2:
      std::cout << "Please enter Y-Axis Minimum: ";
      std::cin >>  tmpopt.starty;
      std::cout << "Please enter Y-Axis Maximum: ";
      std::cin >>tmpopt.stopy;
      tmpopt.autoy = false;
    break;
    case 3:
      std::cout << "Please enter Filename: ";
      std::cin >>  tmpopt.starty;
    break;
    case 4:
      std::cout << "Please enter X Label: ";
      std::cin >>  tmpopt.xlabel;
    break;
    case 5:
      std::cout << "Please enter Y Label: ";
      std::cin >>  tmpopt.ylabel;
    break;
  default:
    std::cout<< "Please enter Interger between 1 and 6\n";

    }
  }while(choice != 6);
    return tmpopt;
}

myoptions parse_batch(std::string bfn, bool &single){
  std::ifstream in;
  in.open(bfn.c_str());
  std::string line; 
  myoptions tmpopt;
  while(getline(in, line)){
    if(boost::find_first(line, "#")) continue;
    if(boost::find_first(line, "startx")){
      std::stringstream sstr;
      std::string tmp;
      sstr << line;
      sstr >> tmp >>tmpopt.startx;
      tmpopt.autox = false;
    }
    if(boost::find_first(line, "starty")){
      std::stringstream sstr;
      std::string tmp;
      sstr << line;
      sstr >> tmp >>tmpopt.starty;
      tmpopt.autoy = false;
    }
    if(boost::find_first(line, "stopx")){
      std::stringstream sstr;
      std::string tmp;
      sstr << line;
      sstr >> tmp >>tmpopt.stopx;
      tmpopt.autox = false;
    }
    if(boost::find_first(line, "stopy")){
      std::stringstream sstr;
      std::string tmp;
      sstr << line;
      sstr >> tmp >>tmpopt.stopx;
      tmpopt.autoy = false;
    }
    if(boost::find_first(line, "plot_name")){
      std::stringstream sstr;
      std::string tmp;
      sstr << line;
      sstr >> tmp >>tmpopt.plot_name;
    }
    if(boost::find_first(line, "xlabel")){
      std::stringstream sstr;
      std::string tmp;
      sstr << line;
      sstr >> tmp >>tmpopt.xlabel;
    }
    if(boost::find_first(line, "ylabel")){
      std::stringstream sstr;
      std::string tmp;
      sstr << line;
      sstr >> tmp >>tmpopt.ylabel;
    }
    if(boost::find_first(line, "single")){
      single = true;
    }
    
  }
  return tmpopt;
}
