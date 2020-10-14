#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <capnp/serialize.h>
#include <automata-safa-capnp/SeparatedAfa.capnp.h>

using namespace automata_safa_capnp::separated_afa;

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    ::capnp::StreamFdMessageReader message(fd);

    SeparatedAfa::Reader afa = message.getRoot<SeparatedAfa>();

    std::cout << "varcount " << afa.getVariableCount() << std::endl;
    std::cout << "qtermcount " << afa.getQterms().size() << std::endl;
    std::cout << "atermcount " << afa.getAterms().size() << std::endl;
    std::cout << "statecount " << afa.getStates().size() << std::endl;

    for(QTerm::Reader qterm : afa.getQterms()) {
        switch(qterm.which()) {
            case QTerm::STATE:
                std::cout << "state " << qterm.getState() << std::endl; break;
            case QTerm::REF:
                std::cout << "ref " << qterm.getRef() << std::endl; break;
            case QTerm::AND:
                std::cout << "and " << qterm.getAnd().size() << std::endl; break;
            case QTerm::OR:
                std::cout << "or " << qterm.getOr().size() << std::endl; break;
            default:
                std::cout << "error" << std::endl; break;
        }
    }

    close(fd);
}
