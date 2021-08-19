#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <capnp/serialize.h>
#include <automata-safa-capnp/Afa/Model/Succinct.capnp.h>
#include <automata-safa-capnp/Afa/Model/Term.capnp.h>

using namespace automata_safa_capnp::model::succinct;
using namespace automata_safa_capnp::model::term;

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    ::capnp::StreamFdMessageReader message(fd);

    BoolAfa::Reader afa = message.getRoot<BoolAfa>();

    std::cout << "varcount " << afa.getVarCount() << std::endl;
    std::cout << "atermcount " << afa.getAterms().size() << std::endl;
    std::cout << "qtermcount " << afa.getMterms().size() << std::endl;
    std::cout << "statecount " << afa.getStates().size() << std::endl;

    for(PredicateQTerm111::Reader mterm : afa.getMterms()) {
        switch(mterm.which()) {
            case PredicateQTerm111::LIT_TRUE:
                std::cout << "true" << std::endl; break;
            case PredicateQTerm111::PREDICATE:
                std::cout << "predicate " << mterm.getPredicate() << std::endl; break;
            case PredicateQTerm111::STATE:
                std::cout << "state " << mterm.getState() << std::endl; break;
            case PredicateQTerm111::OR:
                std::cout << "or";
                for (uint32_t child: mterm.getOr()) {
                  std::cout << " " << child;
                }
                std::cout << std::endl;
                break;
            case PredicateQTerm111::AND:
                std::cout << "and";
                for (uint32_t child: mterm.getAnd()) {
                  std::cout << " " << child;
                }
                std::cout << std::endl;
                break;
            default:
                std::cout << "error" << std::endl; break;
        }
    }

    close(fd);
}
