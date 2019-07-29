#pragma once

#include "SEConfig.hpp"
#include "ADNNanorobot.hpp"
#include "ADNArray.hpp"


  

class MSVColors {
public:
  MSVColors();
  ~MSVColors() = default;

  ADNArray<float> GetColor(ADNPointer<ADNAtom> a);
  ADNArray<float> GetColor(ADNPointer<ADNNucleotide> nt);
  ADNArray<float> GetColor(ADNPointer<ADNSingleStrand> ss);
  ADNArray<float> GetColor(ADNPointer<ADNBaseSegment> bs);
  ADNArray<float> GetColor(ADNPointer<ADNDoubleStrand> ds);
  
  void SetColor(ADNArray<float> color, ADNPointer<ADNAtom> a);
  void SetColor(ADNArray<float> color, ADNPointer<ADNNucleotide> nt);
  void SetColor(ADNArray<float> color, ADNPointer<ADNSingleStrand> ss);
  void SetColor(ADNArray<float> color, ADNPointer<ADNBaseSegment> bs);
  void SetColor(ADNArray<float> color, ADNPointer<ADNDoubleStrand> ds);

  void SetStandardAtomColorScheme();
  void SetStandardNucleotideColorScheme();
  void SetStandardSingleStrandColorScheme();
  void SetStandardDoubleStrandColorScheme();

  void SetAtomColorScheme(ADNArray<float> colorScheme);
  void SetNucleotideColorScheme(ADNArray<float> colorScheme);
  void SetSingleStrandColorScheme(ADNArray<float> colorScheme);
  void SetDoubleStrandColorScheme(ADNArray<float> colorScheme);

  ADNArray<float> GetMaterialColor(SBNode* node);

private:

  template<typename T>
  std::pair<bool, ADNArray<float>> GetColor(T el, std::map<T, ADNArray<float>> & searchMap) {
    ADNArray<float> color = ADNArray<float>(4);
    bool found = false;
    if (searchMap.find(el) != searchMap.end()) {
      color = searchMap.at(el);
      found = true;
    }

    //bool found = false;
    //if (searchMap.size() > 0) {
    //  color = searchMap.at(el);
    //  found = true;
    //}

    return std::make_pair(found, color);
  }

  template<typename T>
  void SetColor(ADNArray<float> color, T el, std::map<T, ADNArray<float>> & searchMap) {
    searchMap[el] = color;
  }
  
  ADNArray<float> defaultbssColor_;

  std::map<ADNAtom*, ADNArray<float>> atomColors_;
  std::map<ADNNucleotide*, ADNArray<float>> ntsColors_;
  std::map<ADNSingleStrand*, ADNArray<float>> sssColors_;
  std::map<ADNBaseSegment*, ADNArray<float>> bssColors_;
  std::map<ADNDoubleStrand*, ADNArray<float>> dssColors_;

  ADNArray<float> atomColorScheme_;
  ADNArray<float> nucleotideColorScheme_;
  ADNArray<float> singleStrandColorScheme_;
  ADNArray<float> doubleStrandColorScheme_;

};