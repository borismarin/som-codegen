
def adapt_python_expression(expr, lang):
    import ast
    import visitors as v
    import sys

    try:
        pt = ast.parse(expr)
    except SyntaxError:
        print ("Problems parsing expressions in the .som file!\n"
               "Please check conformance to python notation!")
        sys.exit(1)
    try:
        visitor = getattr(v, lang)
        #print visitor
    except AttributeError:
        print "Visitor for language '%s' not found! Check visitors.py" % lang
        import sys
        sys.exit(1)
        
    return visitor().visit(pt.body[0].value)