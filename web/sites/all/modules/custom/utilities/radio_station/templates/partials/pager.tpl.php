<?php
if ($pager['last_shown'] <= 1):
  return;
endif;
?>


<nav class="text-center margin-top-lg">
  <ul class="pagination">
    <?php if ($pager['first']): ?>
      <li>
        <a href="<?php print "?{$pager['query_string']}page={$pager['first']}"; ?>">
          <span aria-hidden="true">&laquo;</span>
        </a>
      </li>
    <?php endif; ?>


    <?php if ($pager['prev']): ?>
      <li>
        <a href="<?php print "?{$pager['query_string']}page={$pager['prev']}"; ?>">
          <span aria-hidden="true">&lsaquo;</span>
        </a>
      </li>
    <?php endif; ?>


    <?php for ($i=$pager['first_shown']; $i<=$pager['last_shown']; $i++): ?>
      <li class="<?php if ($i == $pager['current']): ?>active<?php endif; ?>">
        <a href="<?php print "?{$pager['query_string']}page={$i}"; ?>">
          <?php print $i; ?>
        </a>
      </li>
    <?php endfor; ?>


    <?php if ($pager['next']): ?>
      <li>
        <a href="<?php print "?{$pager['query_string']}page={$pager['next']}"; ?>">
          <span aria-hidden="true">&rsaquo;</span>
        </a>
      </li>
    <?php endif; ?>


    <?php if ($pager['last']): ?>
      <li>
        <a href="<?php print "?{$pager['query_string']}page={$pager['last']}"; ?>">
          <span aria-hidden="true">&raquo;</span>
        </a>
      </li>
    <?php endif; ?>
  </ul>
</nav>
