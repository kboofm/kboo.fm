<h2 class="bg-info">
  Recent Playlists
</h2>


<?php foreach ($items as $item): ?>
  <p>
    <?php print $item['program']; ?>
    <br />

    <a href="<?php print $item['url']; ?>">
      <?php print $item['title']; ?>
    </a>
  </p>
<?php endforeach; ?>


<p>
  <a class="more-link bg-info"
     href="#">
    More
  </a>
</p>
