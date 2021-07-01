# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 16:08:41 by aldubar           #+#    #+#              #
#    Updated: 2021/07/01 17:05:09 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM		python:3.7.9-slim

RUN		apt update && python3 -m pip install --upgrade pip setuptools && \
		python3 -m pip install norminette

WORKDIR		/.github/normv3

ENTRYPOINT	[ "norminette" ]
