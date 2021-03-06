<?xml version="1.0" encoding="UTF-8"?>
<rss version="2.0" xmlns:itunes="http://www.itunes.com/dtds/podcast-1.0.dtd" xmlns:atom="http://www.w3.org/2005/Atom">

  <?php $station_name = "KBOO Community Radio"; $station_email = "podcast@kboo.org";?>

  <channel>
	<?php
		if(current_path() == 'audio/feed'):
	?>
		<title>KBOO <?php /*print $program['title'];*/ ?>Community Radio</title>
	<?php
		else:
	?>
		<title><?php print $program['title'];?></title> 
	<?php
		endif;
	?>
    <atom:link href="<?php print $program['podcast_url']; ?>" rel="self" type="application/rss+xml"/>
    <link><?php print $program['url']; ?></link>
<description>KBOO Radio is a community-powered station in Portland Oregon</description>
    <language>en-us</language>
    <copyright>&#x2117; &amp; &#xA9; <?php print date('Y') . " " . $station_name; ?></copyright>
    <itunes:owner><itunes:email><?php print $station_email; ?></itunes:email></itunes:owner>
    <itunes:author>KBOO Radio</itunes:author>
    <itunes:category text="News &amp; Politics"></itunes:category>
    <?php /*<itunes:image href="https://kboo.fm/sites/default/files/kboo_radio_tower.jpg" /> */ ?>
    <itunes:image href="<?php print $items[0]['program_image']; ?>" />
    <itunes:explicit><?php print ($channel_explicit ? 'yes' : 'no'); ?></itunes:explicit>

    <?php foreach ($items as $item): ?>
      <item>
        <title><?php print $item['title']; ?></title>

        <link><?php print $item['url']; ?></link>

        <pubDate><?php print $item['other_pubdate']; ?></pubDate>

        <itunes:author><?php print $station_name ?></itunes:author>

        <itunes:summary><?php print $item['summary']; ?></itunes:summary>

        <?php /*<itunes:image href="https://kboo.fm/sites/default/files/kboo_radio_tower.jpg" />*/ ?>
        <itunes:image href="<?php print $item['image']; ?>" />

	<itunes:explicit><?php print $item['explicit']; ?></itunes:explicit>

        <enclosure url="<?php print $item['audio_file']; ?>" length="<?php print $item['duration']; ?>" type="audio/mpeg"/>

        <guid><?php print $item['url']; ?></guid>

        <itunes:keywords></itunes:keywords>
      </item>
    <?php endforeach; ?>
  </channel>
</rss>
