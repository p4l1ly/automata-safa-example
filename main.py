import capnp
import sys

from automata_safa_capnproto.Afa.Model import Succinct

with open(sys.argv[1], 'r') as f:
    sepafa = Succinct.BoolAfa.read(f)
    print("varcount", sepafa.varCount)
    print("atermcount", len(sepafa.aterms))
    print("mtermcount", len(sepafa.mterms))
    print("statecount", len(sepafa.states))

    for mterm in sepafa.mterms:
        which = mterm.which()
        if which == "litTrue":
            print("true")
        elif which == "predicate":
            print("predicate", mterm.predicate)
        elif which == "state":
            print("state", mterm.state)
        elif which == "and":
            print("and", len(getattr(mterm, "and")))
        elif which == "or":
            print("or", len(getattr(mterm, "or")))
