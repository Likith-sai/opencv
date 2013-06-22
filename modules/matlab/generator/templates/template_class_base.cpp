{% import 'functional.cpp' as functional %}
/*
 * file:   {{clss.name}}Bridge.cpp
 * author: A trusty code generator
 * date:   {{time.strftime("%a, %d %b %Y %H:%M:%S", time.localtime())}}
 * 
 * This file was autogenerated, do not modify.
 * See LICENCE for full modification and redistribution details.
 * Copyright {{time.strftime("%Y", time.localtime())}} The OpenCV Foundation
 */
#include "mex.h"
#include "bridge.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <opencv2/core.hpp>
{% block includes %}
{% endblock %}

namespace {

typedef std::unordered_map Map;
typedef std::vector<Bridge> (*)({{clss.name}}&, const std::vector<Bridge>&) MethodSignature;

{% for function in clss.functions %}
// wrapper for {{function.name}}() method
std::vector<Bridge> {{function.name}}({{clss.name}}& inst, const std::vector<Bridge>& args) {
  // setup

  // invoke
  {{ functional.generate(function) }}

  // setdown
}

{% endfor %}

map<std::string, MethodSignature> createMethodMap() {
  Map<std::string, MethodSignature> m;
  {% for function in clss.functions -%}
  m["{{function.name}}"] = &{{function.name}};
  {% endfor %}

  return m;
}
static const Map<std::string, MethodSignature> methods = createMethodMap();

// map of created {{clss.name}} instances. Don't trust the user to keep them safe...
static Map<void *, {{clss.name}}> instances;

/* 
 * {{ clss.name }}
 * Gateway routine
 *   nlhs - number of return arguments
 *   plhs - pointers to return arguments
 *   nrhs - number of input arguments
 *   prhs - pointers to input arguments
 */
void mexFunction(int nlhs, mxArray* plhs[],
                 int nrhs, const mxArray* prhs[]) {

  // parse the inputs
  Bridge method_name(prhs[0]);

  Bridge handle(prhs[1]);
  std::vector<Bridge> brhs(prhs+2, prhs+nrhs);

  // retrieve the instance of interest
  try {
    {{clss.name}}& inst = instances.at(handle.address());
  } catch (const std::out_of_range& e) {
    mexErrMsgTxt("Invalid object instance provided");
  }

  // invoke the correct method on the data
  try {
    std::vector<Bridge> blhs = (*methods.at(method_name))(inst, brhs);
  } catch (const std::out_of_range& e) {
    mexErrMsgTxt("Unknown method specified");
  }

  {% block postfun %}
  {% endblock %}

  {% block cleanup %}
  {% endblock %}

}

}; // end namespace
