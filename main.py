import capnp
import sys

from automata_safa_capnproto import SeparatedAfa_capnp

with open(sys.argv[1], 'r') as f:
    sepafa = SeparatedAfa_capnp.SeparatedAfa.read(f)
    print("varcount", sepafa.variableCount)
    print("qtermcount", len(sepafa.qterms))
    print("atermcount", len(sepafa.aterms))
    print("statecount", len(sepafa.aterms))

    for qterm in sepafa.qterms:
        which = qterm.which()
        if which == "state":
            print("state", qterm.state)
        elif which == "ref":
            print("ref", qterm.ref)
        elif which == "and":
            print("and", len(getattr(qterm, "and")))
        elif which == "or":
            print("or", len(getattr(qterm, "or")))
