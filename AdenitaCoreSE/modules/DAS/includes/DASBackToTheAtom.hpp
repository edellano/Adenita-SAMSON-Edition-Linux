#pragma once
#ifndef BACKTOTHEATOM_H
#define BACKTOTHEATOM_H


#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "SBProxy.hpp"
#include "SBDDataGraphNode.hpp"
#include "SBStructuralModel.hpp"
#include "SAMSON.hpp"
#include "SBChain.hpp"
#include "SBMolecule.hpp"
#include "ADNNanorobot.hpp"
#include "ADNVectorMath.hpp"
#include "ADNBasicOperations.hpp"
#include "DASPolyhedron.hpp"


typedef std::map<int, std::vector<double>> BasePositions;
typedef std::map<DASEdge*, BasePositions> SequencePositions;
typedef std::pair<ADNPointer<ADNNucleotide>, ADNPointer<ADNNucleotide>> NtPair;

class DASBackToTheAtom {
public:

  DASBackToTheAtom();
  ~DASBackToTheAtom();

  /**
   * Sets the nucleotides backbone, sidechain and center of mass positions for an entire
   * double strand using the BaseSegment position information.
   * \param The double strand whose nucleotides need to be set.
   */
  void SetDoubleStrandPositions(ADNPointer<ADNDoubleStrand> ds);
  void SetNucleotidesPostions(ADNPointer<ADNPart> part);

  void SetPositionLoopNucleotides(ADNPointer<ADNBaseSegment> bs);

  void GenerateAllAtomModel(ADNPointer<ADNPart> origami);
  
  void CheckDistances(ADNPointer<ADNPart> part);

  void PopulateWithMockAtoms(ADNPointer<ADNPart> origami, bool positionsFromNucleotide = false, bool createAtoms = false);

  //! Set the backbone and sidechain position of the nucleotides of a base segment
  /*!
    \param The nucleotide we want to untwist
    \param Whether to also untwist the pair
  */
  void SetNucleotidePosition(ADNPointer<ADNBaseSegment> bs, bool set_pair);
  //! Untwist the nucleotides of a base segment (remove the helix turn)
  /*!
    \param The base segment
    \param Whether to also untwist the pair
  */
  void UntwistNucleotidesPosition(ADNPointer<ADNBaseSegment> bs);

  //! Sets the positions of a collection of nucleotides, meant to be called after modifications
  void SetPositionsForNewNucleotides(ADNPointer<ADNPart> part, CollectionMap<ADNNucleotide> nts, bool all_atoms = false);

  //void SetAllAtomsPostions(ADNPointer<ADNPart> origami);
  // for cadnano
  /*void SetAllAtomsPostions2D(ADNPointer<ADNPart> origami);
  void SetAllAtomsPostions1D(ADNPointer<ADNPart> origami);*/

  /**
   * Rotates a nucleotide along base-pair plane (defined by nt->e3_).
   * \param the nucleotide you want to rotate
   * \param the amount of degrees
   * \param wether to also rotate the pair
   */
  //void RotateNucleotide(ADNPointer<ADNNucleotide> nt, double angle, bool set_pair);

  /**
   * Loads a nucleotide or base pair into SAMSON for testing purposes
   */
  //void DisplayDNABlock(std::string block);

private:
  ADNPointer<ADNNucleotide> da_;
  ADNPointer<ADNNucleotide> dt_;
  ADNPointer<ADNNucleotide> dg_;
  ADNPointer<ADNNucleotide> dc_;
  NtPair da_dt_;
  NtPair dt_da_;
  NtPair dc_dg_;
  NtPair dg_dc_;
  /** Loads the four types of nucleotide as members
  */
  void LoadNucleotides();
  /** Loads the four base pairs as members
  */
  void LoadNtPairs();
  /** Parses a nucleotide PDB file.
   *  \param a string with the location of the PDB.
   *  \return a nucleotide object.
   */
  ADNPointer<ADNNucleotide> ParsePDB(std::string source);
  /** Parses a base pair PDB file.
   *  \param a string with the location of the PDB.
   *  \return a pair of nucleotide objects.
   */
  NtPair ParseBasePairPDB(std::string source);

  void PositionLoopNucleotides(ADNPointer<ADNLoop> loop, SBPosition3 bsPositionPrev, SBPosition3 bsPositionNext);
  void PositionLoopNucleotidesQBezier(ADNPointer<ADNLoop> loop, SBPosition3 bsPositionPrev, SBPosition3 bsPositionNext, SBVector3 bsPrevE3, SBVector3 bsNextE3);

  void PopulateNucleotideWithAllAtoms(ADNPointer<ADNPart> origami, ADNPointer<ADNNucleotide> nt);
  void CreateBonds(ADNPointer<ADNPart> origami);
  void FindAtomsPositions(ADNPointer<ADNNucleotide> nt);

  //! Untwist the nucleotide (remove the helix turn)
  /*!
  \param The nucleotide we want to untwist
  \param Whether to also untwist the pair
  */
  void UntwistNucleotidePosition(ADNPointer<ADNNucleotide> nt);

  //! Create positions matrix from a NtPair, every row in the matrix is the position of one atom
  ublas::matrix<double> CreatePositionsMatrix(NtPair pair);
  //! Select the ideal NtPair corresponding to a pair
  NtPair GetIdealBasePairNucleotides(ADNPointer<ADNNucleotide> nt_l, ADNPointer<ADNNucleotide> nt_r);
  NtPair GetIdealBasePairNucleotides(DNABlocks nt_l, DNABlocks nt_r);
  //! If not defined, set a local basis for the base segment and return it as a matrix
  ublas::matrix<double> CalculateBaseSegmentBasis(ADNPointer<ADNBaseSegment> bs);
  /*!
   * Calculate the center of mass of backbone and sidechain w.r.t. atom coordinates
   *  \param the nucleotide
   *  \return tuple with center values. first is total c.o.m., second is backbone, third is sidechain.
   */
  static std::tuple<SBPosition3, SBPosition3, SBPosition3> CalculateCenters(ADNPointer<ADNNucleotide> nt);
  static std::tuple<SBPosition3, SBPosition3, SBPosition3> CalculateCentersOfMass(ADNPointer<ADNNucleotide> nt);
  /*!
   * Generate a SBPosition from a ublas vector assuming picometers -> angstrom conversion
   */
  static SBPosition3 UblasToSBPosition(ublas::vector<double> vec);
  /*!
   * Sets the reference frame for the pair to the standard basis
   */
  void SetReferenceFrame(NtPair pair);
  /** Sets the positions of a list of atoms according to a matrix positions
  */
  int SetAtomsPositions(CollectionMap<ADNAtom> atoms, ublas::matrix<double> new_positions, int r_id);
  /**
   * 
   */
  ADNPointer<ADNAtom> CopyAtom(ADNPointer<ADNAtom> atom);
};

#endif