# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Dockerfile                                         :+:    :+:             #
#                                                      +:+                     #
#    By: tde-jong <tde-jong@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/05/26 18:05:06 by tde-jong       #+#    #+#                 #
#    Updated: 2019/05/26 18:05:49 by tde-jong      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

FROM ubuntu:14.04

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN add-apt-repository -y ppa:snaipewastaken/ppa
RUN apt-get update
RUN apt-get install -y make
RUN apt-get install -y gcc
RUN apt-get install -y criterion-dev
RUN apt-get install -y libncurses5-dev libncursesw5-dev
RUN apt-get install -y valgrind

WORKDIR /vsh
