#pragma once
#include "DxLib.h"
#include <vector>
#include <iostream>
#include <string>

namespace draw_string_center_impl {
	std::vector<DRAWCHARINFO> get_draw_string_char_info(const std::basic_string<TCHAR>& string, int font_handle) {
		std::vector<DRAWCHARINFO> info;
		info.resize(string.size());
		auto char_info_num = GetDrawStringCharInfoToHandle(info.data(), info.size(), string.c_str(), string.length() * sizeof(TCHAR), font_handle, false);
		if (char_info_num < 0) throw std::runtime_error("fail in function DxLib::GetDrawStringCharInfoToHandle");
		if (info.size() < static_cast<std::size_t>(char_info_num)) {
			info.resize(char_info_num + 1);
			//再取得
			char_info_num = GetDrawStringCharInfoToHandle(info.data(), info.size(), string.c_str(), string.length() * sizeof(TCHAR), font_handle, false);
			if (char_info_num < 0 || info.size() < static_cast<std::size_t>(char_info_num)) throw std::runtime_error("fail to detect draw info.");
		}
		info.resize(char_info_num);
		return info;
	}
}
float draw_string_center(
	float draw_area_x_left, float draw_area_x_right, float draw_area_y_top, float draw_area_y_bottom,
	const std::basic_string<TCHAR>& string,
	unsigned int color, int font_handle,
	unsigned int edge_color = 0
)
{
	if (0 == string.length())  throw std::invalid_argument("empty string not allowed.");
	if (draw_area_x_right < draw_area_x_left || draw_area_y_bottom < draw_area_y_top) throw std::invalid_argument("");

	//一文字ずつの描画幅情報を取得する
	const auto info = draw_string_center_impl::get_draw_string_char_info(string, font_handle);

	//ManageData->LineSpaceValidFlag ? ManageData->LineSpace : ManageData->BaseInfo.FontHeight
	const auto line_space = DxLib::GetFontLineSpaceToHandle(font_handle);
	const float area_width = draw_area_x_right - draw_area_x_left;
	const auto total_draw_width = info.back().DrawX + info.back().SizeX - info.front().DrawX;
	if (total_draw_width <= area_width) {
		//一行ですむ場合
		const float padding = (area_width - total_draw_width) / 2.0f;
		DxLib::DrawStringFToHandle(draw_area_x_left + padding, draw_area_y_top, string.c_str(), color, font_handle, edge_color, false);
		return static_cast<float>(line_space);
	}

	//複数行になる場合

	const float area_height = draw_area_y_bottom - draw_area_y_top;

	//描画開始
	std::size_t current_string_byte_pos = 0;
	std::size_t line_front_string_byte_pos = 0;
	float current_y_relative = 0.0f;
	auto line_front_it = info.begin();
	for (auto it = info.begin(); it < info.end(); current_string_byte_pos += it->Bytes, ++it) {
		const auto line_width_contain_current_it_point_char = it->DrawX + it->SizeX - line_front_it->DrawX;
		if (area_width < line_width_contain_current_it_point_char) {
			using namespace std::string_literals;
			//次の行に行く前に描画、itが指す文字は含まない
			const std::size_t str_len_byte = current_string_byte_pos - line_front_string_byte_pos;
			//it->DrawXは前の文字の右端に等しい
			const float line_width = it->DrawX - line_front_it->DrawX;
			const float padding = (area_width - line_width) / 2.0f;
			const auto line_string = string.substr(line_front_string_byte_pos / sizeof(TCHAR), (str_len_byte / sizeof(TCHAR)));
			DxLib::DrawStringFToHandle(draw_area_x_left + padding, draw_area_y_top + current_y_relative, line_string.c_str(), color, font_handle, edge_color, false);
			//itが指す文字が先頭になる
			line_front_string_byte_pos = current_string_byte_pos;
			current_y_relative += line_space;
			line_front_it = it;
			if (area_height < current_y_relative) return current_y_relative;//描画可能領域(y)を超えたら終了
		}
	}
	//最終行の描画
	const auto last_line_width = info.back().DrawX + info.back().SizeX - line_front_it->DrawX;
	const float padding = (area_width - last_line_width) / 2.0f;
	const auto line_string = string.substr(line_front_string_byte_pos / sizeof(TCHAR));
	DxLib::DrawStringFToHandle(draw_area_x_left + padding, draw_area_y_top + current_y_relative, line_string.c_str(), color, font_handle, edge_color, false);
	return current_y_relative + line_space;
}