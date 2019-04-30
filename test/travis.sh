#!/bin/bash
make && make fclean && make test_norm && make test_coverage && bash <(curl -s https://codecov.io/bash)
