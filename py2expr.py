import ast
import visitors as v

def adapt_python_expression(expr, lang):

    pt = ast.parse(expr)
    try:
        visitor = getattr(v, lang)
        #print visitor
    except AttributeError:
        print "Visitor for language '%s' not found! Check visitors.py" % lang
        import sys
        sys.exit(1)
        
    return visitor().visit(pt.body[0].value)