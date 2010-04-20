/*
 * TextOutput.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef TEXTOUTPUT_HPP_
#define TEXTOUTPUT_HPP_

#include <QPlainTextEdit>

#include <iostream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/categories.hpp>

class TextOutput: public QPlainTextEdit
{
Q_OBJECT

	template<typename Appender>
	class Sink
	{
	public:
		typedef char char_type;
		typedef boost::iostreams::sink_tag category;

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
				outstream(outsink), errstream(errsink)
	{
		outbuf = std::cout.rdbuf(outstream.rdbuf());
		errbuf = std::cerr.rdbuf(errstream.rdbuf());
		logbuf = std::clog.rdbuf(outstream.rdbuf());
		setReadOnly(true);
	}

	~TextOutput()
	{
		std::cout.rdbuf(outbuf);
		std::cerr.rdbuf(errbuf);
		std::clog.rdbuf(logbuf);
	}

private:
	Sink<OutAppender> outsink;
	Sink<ErrAppender> errsink;

	boost::iostreams::stream<Sink<OutAppender> > outstream;
	boost::iostreams::stream<Sink<ErrAppender> > errstream;

	std::streambuf* outbuf;
	std::streambuf* errbuf;
	std::streambuf* logbuf;
};

#endif /* TEXTOUTPUT_HPP_ */
