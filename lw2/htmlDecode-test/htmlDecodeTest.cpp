#include "pch.h"
#include "../htmlDecode/htmlDecode.h"

TEST_CASE("htmlDecode test")
{
	CHECK(HtmlDecode("") == "");
	CHECK(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M's");
	CHECK(HtmlDecode("&quot;&apos;&lt;&gt;&amp;") == "\"'<>&");
	CHECK(HtmlDecode("&quot") == "&quot");
	CHECK(HtmlDecode(";&amp;;&apos") == ";&;&apos");
	CHECK(HtmlDecode("&amp;lt;") == "&lt;");
}