/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_union.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 14:15:10 by yderosie          #+#    #+#             */
/*   Updated: 2015/12/16 14:15:11 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UNION_H
# define PARSER_UNION_H

union			u_data {
	struct s_json		*obj;
	struct s_json_arr	*arr;
	int					boolean;
	char				*s;
	double				number;
}				data;

#endif
