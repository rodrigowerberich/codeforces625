#include "PreviousLetter.hh"

std::ostream& operator <<(std::ostream& os, const PreviousLetter& previousLetter){
    if(!previousLetter.valid){
        return os << "No previous letter";
    }else{
        return os << previousLetter.previous;
    }
}