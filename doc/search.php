<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<!-- 
	Copyright (C) 2007, 2008, 2009, 2010, 2011. PARP Research Group.
	<http://perception.inf.um.es>
	University of Murcia, Spain.

	This file is part of the QVision library.

	QVision is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, version 3 of the License.

	QVision is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with QVision. If not, see <http://www.gnu.org/licenses/>.
-->

<html><head><meta http-equiv="content-Type" content="text/html;charset=UTF-8">
<title>QVision: Qt&#39;s Image, Video and Computer Vision Library</title>
<meta name="title" content="QVision" />
<meta name="dc.title" content="QVision" />
<meta name="url" content="http://perception.inf.um.es/QVision" />
<meta name="author" content="PARP Research Group - http://perception.inf.um.es" />
<meta name="revisit-after" content="30 DAYS"/>
<meta name="robots" content="index,follow"/>
<meta name="classification" content="*">
<meta name="rating" content="Safe For Kids">
<meta name="distribution" content="GLOBAL"/>
<meta name="description" content="Qt's Image, Video and Computer Vision Library"/>
<meta name="page-topic" content="Computer Vision research and prototype programming"/>
<meta name="geo.country" content="ES" />

<!--
Keywords:
By license:		open source, gnu, lgpl, gpl, free
By theme:		computer vision, image processing, robotics, programming, source, development
By usage:		library, toolkit, framework, prototype, application
By programming specs:	object oriented, c++, block programming, reusability, gui, graphical, parallel computing, high performance, GPU, prototyping
Interoperability with:	Qt, GSL, GNU Scientific library, OpenCV, CGAL, QWT, CUDA, mplayer, IPP, Intel Image Performance Primitives, blas, lapack
Functionallity:		image features, matrix algebra, projective geometry, mser, function minimization, function optimization, canny operator, harris operator, corner detection, performance evaluation, cpu usage, graphical interface
Main data-types:	matrix, vector, tensor, quaternion, image, polyline
Video sources:		webcam, camera, stream
Devices:		embedded, desktop computer, laptop, mini-laptop
Authors:		PARP research group. University of Murcia, Spain.
-->

<meta name="keywords" content="augmented reality, sfm, structure from motion, open source, gnu, lgpl, gpl, free, computer vision, image processing, robotics, programming, source, development, library, toolkit, framework, prototype, application, object oriented, c++, block programming, reusability, gui, graphical, parallel computing, high performance, GPU, prototyping, Qt, GSL, GNU Scientific library, OpenCV, CGAL, QWT, CUDA, mplayer, IPP, Intel Image Performance Primitives, blas, lapack, image features, matrix algebra, projective geometry, mser, function minimization, function optimization, canny operator, harris operator, corner detection, performance evaluation, cpu usage, graphical interface, matrix, vector, tensor, quaternion, image, polyline, webcam, camera, stream, embedded, desktop computer, laptop, mini-laptop, University of Murcia, Spain, PARP research group, vision por computador"/>
<meta http-equiv="keywords" content="augmented reality, sfm, structure from motion, open source, gnu, lgpl, gpl, free, computer vision, image processing, robotics, programming, source, development, library, toolkit, framework, prototype, application, object oriented, c++, block programming, reusability, gui, graphical, parallel computing, high performance, GPU, prototyping, Qt, GSL, GNU Scientific library, OpenCV, CGAL, QWT, CUDA, mplayer, IPP, Intel Image Performance Primitives, blas, lapack, image features, matrix algebra, projective geometry, mser, function minimization, function optimization, canny operator, harris operator, corner detection, performance evaluation, cpu usage, graphical interface, matrix, vector, tensor, quaternion, image, polyline, webcam, camera, stream, embedded, desktop computer, laptop, mini-laptop, University of Murcia, Spain, PARP research group, vision por computador"/>
<meta http-equiv="pragma" content="no-cache"/>
<meta http-equiv="title" content="QVision"/>
<link href="doxygen.css" rel="stylesheet" type="text/css" />
<link href="tabs.css" rel="stylesheet" type="text/css" />
<link rel="shortcut icon" href="favicon.ico" />
</head><body>

<table width="100%"><tr>
	<td><a href="http://perception.inf.um.es/"><img src="parp.png" border="0" /> <big>PARP Research Group</big></a></td>
	<td align="right"><a href="http://www.um.es/"><big>Universidad de Murcia</big> <img src="um.png" border="0" /></a></td>
</tr></table>

<hr /><br />

<table width="95%" align="center"><tr><td>

<!-- Generated by Doxygen 1.6.3 -->
<script type="text/javascript"><!--
var searchBox = new SearchBox("searchBox", "search",false,'Search');
--></script>
  <div class="tabs">
    <ul>
      <li><a href="index.html"><span>Main&nbsp;Page</span></a></li>
      <li><a href="pages.html"><span>Related&nbsp;Pages</span></a></li>
      <li><a href="modules.html"><span>Modules</span></a></li>
      <li><a href="annotated.html"><span>Classes</span></a></li>
      <li><a href="files.html"><span>Files</span></a></li>
      <li>
        <div id="MSearchBox" class="MSearchBoxInactive">
          <form id="FSearchBox" action="search.php" method="get">
            <img id="MSearchSelect" src="search/search.png" alt=""/>

<script language="php">

function search_results()
{
  return "Search Results";
}

function matches_text($num)
{
  if ($num==0)
  {
    return "Sorry, no documents matching your query.";
  }
  else if ($num==1)
  {
    return "Found <b>1</b> document matching your query.";
  }
  else // $num>1
  {
    return "Found <b>$num</b> documents matching your query. Showing best matches first.";
  }
}

function report_matches()
{
  return "Matches: ";
}
function end_form($value)
{
  echo "            <input type=\"text\" id=\"MSearchField\" name=\"query\" value=\"$value\" size=\"20\" accesskey=\"S\" onfocus=\"searchBox.OnSearchFieldFocus(true)\" onblur=\"searchBox.OnSearchFieldFocus(false)\"/>\n          </form>\n        </div>\n      </li>\n    </ul>\n  </div>\n";
}

function readInt($file)
{
  $b1 = ord(fgetc($file)); $b2 = ord(fgetc($file));
  $b3 = ord(fgetc($file)); $b4 = ord(fgetc($file));
  return ($b1<<24)|($b2<<16)|($b3<<8)|$b4;
}

function readString($file)
{
  $result="";
  while (ord($c=fgetc($file))) $result.=$c;
  return $result;
}

function readHeader($file)
{
  $header =fgetc($file); $header.=fgetc($file);
  $header.=fgetc($file); $header.=fgetc($file);
  return $header;
}

function computeIndex($word)
{
  // Simple hashing that allows for substring search
  if (strlen($word)<2) return -1;
  // high char of the index
  $hi = ord($word{0});
  if ($hi==0) return -1;
  // low char of the index
  $lo = ord($word{1});
  if ($lo==0) return -1;
  // return index
  return $hi*256+$lo;
}

function search($file,$word,&$statsList)
{
  $index = computeIndex($word);
  if ($index!=-1) // found a valid index
  {
    fseek($file,$index*4+4); // 4 bytes per entry, skip header
    $index = readInt($file);
    if ($index) // found words matching the hash key
    {
      $start=sizeof($statsList);
      $count=$start;
      fseek($file,$index);
      $w = readString($file);
      while ($w)
      {
        $statIdx = readInt($file);
        if ($word==substr($w,0,strlen($word)))
        { // found word that matches (as substring)
          $statsList[$count++]=array(
              "word"=>$word,
              "match"=>$w,
              "index"=>$statIdx,
              "full"=>strlen($w)==strlen($word),
              "docs"=>array()
              );
        }
        $w = readString($file);
      }
      $totalHi=0;
      $totalFreqHi=0;
      $totalFreqLo=0;
      for ($count=$start;$count<sizeof($statsList);$count++)
      {
        $statInfo = &$statsList[$count];
        $multiplier = 1;
        // whole word matches have a double weight
        if ($statInfo["full"]) $multiplier=2;
        fseek($file,$statInfo["index"]); 
        $numDocs = readInt($file);
        $docInfo = array();
        // read docs info + occurrence frequency of the word
        for ($i=0;$i<$numDocs;$i++)
        {
          $idx=readInt($file); 
          $freq=readInt($file); 
          $docInfo[$i]=array("idx"  => $idx,
                             "freq" => $freq>>1,
                             "rank" => 0.0,
                             "hi"   => $freq&1
                            );
          if ($freq&1) // word occurs in high priority doc
          {
            $totalHi++;
            $totalFreqHi+=$freq*$multiplier;
          }
          else // word occurs in low priority doc
          {
            $totalFreqLo+=$freq*$multiplier;
          }
        }
        // read name and url info for the doc
        for ($i=0;$i<$numDocs;$i++)
        {
          fseek($file,$docInfo[$i]["idx"]);
          $docInfo[$i]["name"]=readString($file);
          $docInfo[$i]["url"]=readString($file);
        }
        $statInfo["docs"]=$docInfo;
      }
      $totalFreq=($totalHi+1)*$totalFreqLo + $totalFreqHi;
      for ($count=$start;$count<sizeof($statsList);$count++)
      {
        $statInfo = &$statsList[$count];
        $multiplier = 1;
        // whole word matches have a double weight
        if ($statInfo["full"]) $multiplier=2;
        for ($i=0;$i<sizeof($statInfo["docs"]);$i++)
        {
          $docInfo = &$statInfo["docs"];
          // compute frequency rank of the word in each doc
          $freq=$docInfo[$i]["freq"];
          if ($docInfo[$i]["hi"])
          {
            $statInfo["docs"][$i]["rank"]=
              (float)($freq*$multiplier+$totalFreqLo)/$totalFreq;
          }
          else
          {
            $statInfo["docs"][$i]["rank"]=
              (float)($freq*$multiplier)/$totalFreq;
          }
        }
      }
    }
  }
  return $statsList;
}

function combine_results($results,&$docs)
{
  foreach ($results as $wordInfo)
  {
    $docsList = &$wordInfo["docs"];
    foreach ($docsList as $di)
    {
      $key=$di["url"];
      $rank=$di["rank"];
      if (in_array($key, array_keys($docs)))
      {
        $docs[$key]["rank"]+=$rank;
      }
      else
      {
        $docs[$key] = array("url"=>$key,
            "name"=>$di["name"],
            "rank"=>$rank
            );
      }
      $docs[$key]["words"][] = array(
               "word"=>$wordInfo["word"],
               "match"=>$wordInfo["match"],
               "freq"=>$di["freq"]
               );
    }
  }
  return $docs;
}

function filter_results($docs,&$requiredWords,&$forbiddenWords)
{
  $filteredDocs=array();
  while (list ($key, $val) = each ($docs)) 
  {
    $words = &$docs[$key]["words"];
    $copy=1; // copy entry by default
    if (sizeof($requiredWords)>0)
    {
      foreach ($requiredWords as $reqWord)
      {
        $found=0;
        foreach ($words as $wordInfo)
        { 
          $found = $wordInfo["word"]==$reqWord;
          if ($found) break;
        }
        if (!$found) 
        {
          $copy=0; // document contains none of the required words
          break;
        }
      }
    }
    if (sizeof($forbiddenWords)>0)
    {
      foreach ($words as $wordInfo)
      {
        if (in_array($wordInfo["word"],$forbiddenWords))
        {
          $copy=0; // document contains a forbidden word
          break;
        }
      }
    }
    if ($copy) $filteredDocs[$key]=$docs[$key];
  }
  return $filteredDocs;
}

function compare_rank($a,$b)
{
  if ($a["rank"] == $b["rank"]) 
  {
    return 0;
  }
  return ($a["rank"]>$b["rank"]) ? -1 : 1; 
}

function sort_results($docs,&$sorted)
{
  $sorted = $docs;
  usort($sorted,"compare_rank");
  return $sorted;
}

function report_results(&$docs)
{
  echo "<table cellspacing=\"2\">\n";
  echo "  <tr>\n";
  echo "    <td colspan=\"2\"><h2>".search_results()."</h2></td>\n";
  echo "  </tr>\n";
  $numDocs = sizeof($docs);
  if ($numDocs==0)
  {
    echo "  <tr>\n";
    echo "    <td colspan=\"2\">".matches_text(0)."</td>\n";
    echo "  </tr>\n";
  }
  else
  {
    echo "  <tr>\n";
    echo "    <td colspan=\"2\">".matches_text($numDocs);
    echo "\n";
    echo "    </td>\n";
    echo "  </tr>\n";
    $num=1;
    foreach ($docs as $doc)
    {
      echo "  <tr>\n";
      echo "    <td align=\"right\">$num.</td>";
      echo     "<td><a class=\"el\" href=\"".$doc["url"]."\">".$doc["name"]."</a></td>\n";
      echo "  <tr>\n";
      echo "    <td></td><td class=\"tiny\">".report_matches()." ";
      foreach ($doc["words"] as $wordInfo)
      {
        $word = $wordInfo["word"];
        $matchRight = substr($wordInfo["match"],strlen($word));
        echo "<b>$word</b>$matchRight(".$wordInfo["freq"].") ";
      }
      echo "    </td>\n";
      echo "  </tr>\n";
      $num++;
    }
  }
  echo "</table>\n";
}

function main()
{
  if(strcmp('4.1.0', phpversion()) > 0) 
  {
    die("Error: PHP version 4.1.0 or above required!");
  }
  if (!($file=fopen("search/search.idx","rb"))) 
  {
    die("Error: Search index file could NOT be opened!");
  }
  if (readHeader($file)!="DOXS")
  {
    die("Error: Header of index file is invalid!");
  }
  $query="";
  if (array_key_exists("query", $_GET))
  {
    $query=$_GET["query"];
  }
  end_form(preg_replace("/[^a-zA-Z0-9\-\_\.]/i", " ", $query ));
  echo "&nbsp;\n<div class=\"searchresults\">\n";
  $results = array();
  $requiredWords = array();
  $forbiddenWords = array();
  $foundWords = array();
  $word=strtok($query," ");
  while ($word) // for each word in the search query
  {
    if (($word{0}=='+')) { $word=substr($word,1); $requiredWords[]=$word; }
    if (($word{0}=='-')) { $word=substr($word,1); $forbiddenWords[]=$word; }
    if (!in_array($word,$foundWords))
    {
      $foundWords[]=$word;
      search($file,strtolower($word),$results);
    }
    $word=strtok(" ");
  }
  $docs = array();
  combine_results($results,$docs);
  // filter out documents with forbidden word or that do not contain
  // required words
  $filteredDocs = filter_results($docs,$requiredWords,$forbiddenWords);
  // sort the results based on rank
  $sorted = array();
  sort_results($filteredDocs,$sorted);
  // report results to the user
  report_results($sorted);
  echo "</div>\n";
  fclose($file);
}

main();


</script>
</td></tr></table>

<br /><hr><br />
<center><a href="http://perception.inf.um.es/QVision">QVision framework</a>.
<a href="http://perception.inf.um.es">PARP research group</a>.
Copyright &copy; 2007, 2008, 2009, 2010, 2011.</center>
<br />
</body>
</html>
