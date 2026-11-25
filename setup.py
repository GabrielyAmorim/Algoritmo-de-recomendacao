from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "nosso_solver",
        ["binding.cpp", "listaCompras.cpp", "similaridade.cpp", "recomendacao.cpp", "solver.cpp"],
        cxx_std=17,
    ),
]

setup(
    name="nosso_solver",
    version="0.1.0",
    description="Integração Python + C++ com pybind11 do sistema de recomendacao",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)