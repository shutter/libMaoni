/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAONI_TEXTOUTPUT_HPP
#define MAONI_TEXTOUTPUT_HPP

#include <QPlainTextEdit>

#include <iostream>
#include <boost/iostreams/tee.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/categories.hpp>

namespace bio = boost::iostreams;

class TextOutput: public QPlainTextEdit
{
	Q_OBJECT

	template<typename Appender>
	class Sink
	{
	public:
		typedef char char_type;
		typedef bio::sink_tag category;

		Sink(QPlainTextEdit* text_edit) :
			text_edit(text_edit)
		{
		}

		std::streamsize write(const char* s, std::streamsize n)
		{
			std::string string(s, n);
			Appender::append(text_edit, string);
			return string.length();
		}

	private:
		QPlainTextEdit* text_edit;
	};

	struct OutAppender
	{
		static void append(QPlainTextEdit* text_edit, std::string const& string)
		{
			text_edit->appendPlainText(QString::fromStdString(string).trimmed());
		}
	};

	struct ErrAppender
	{
		static void append(QPlainTextEdit* text_edit, std::string const& string)
		{
			QString qstring = QString::fromStdString(string).trimmed();
			text_edit->appendHtml("<b>" + qstring + "</b>");
		}
	};

public:
	TextOutput(QWidget * parent = 0) :
		QPlainTextEdit(parent), outsink(this), errsink(this),
			outtee(*std::cout.rdbuf(), outsink),
			errtee(*std::cerr.rdbuf(), errsink),
			logtee(*std::clog.rdbuf(), outsink),
			out(outtee), err(errtee), log(logtee)
	{
		outbuf = std::cout.rdbuf(out.rdbuf());
		errbuf = std::cerr.rdbuf(err.rdbuf());
		logbuf = std::clog.rdbuf(out.rdbuf());
		setReadOnly(true);
	}

	~TextOutput()
	{
		std::cout.rdbuf(outbuf);
		std::cerr.rdbuf(errbuf);
		std::clog.rdbuf(logbuf);
	}

private:
	typedef Sink<OutAppender> outsink_type;
	typedef Sink<ErrAppender> errsink_type;

	typedef bio::tee_device<std::streambuf, outsink_type> outtee_type;
	typedef bio::tee_device<std::streambuf, errsink_type> errtee_type;

	outsink_type outsink;
	errsink_type errsink;

	outtee_type outtee;
	errtee_type errtee;
	outtee_type logtee;

	bio::stream<outtee_type> out;
	bio::stream<errtee_type> err;
	bio::stream<outtee_type> log;

	std::streambuf* outbuf;
	std::streambuf* errbuf;
	std::streambuf* logbuf;
};

#endif /* MAONI_TEXTOUTPUT_HPP */
