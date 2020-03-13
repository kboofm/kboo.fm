/**
 * @file
 * Utilities useful for manipulating media in wysiwyg editors.
 */

(function ($) {

"use strict";

Drupal.media = Drupal.media || {};

Drupal.media.utils = {

  /**
   * Align placeholder media element in wysiwyg editors.
   *
   * @param {jQuery} $element
   *   The media element placeholder as a jQuery object.
   * @param {string} value
   *   The alignment value. Allowed values are 'left', 'center' or 'right'.
   * @param {bool} toggle
   *   Optional. If true (set), this will toggle the alignment.
   *
   * @return {bool}
   *   true if alignment was set to given value, false otherwise.
   */
  alignMedia: function ($element, value, toggle) {
    if (!$element.hasClass('media-element')) {
      return false;
    }
    var currentAlignment = this.getMediaAlignment($element);
    if (currentAlignment == value) {
      if (toggle) {
        resetAlignment($element);
        return false;
      }
      return true;
    }
    else {
      if (currentAlignment) {
        resetAlignment($element);
      }
      setAlignment($element, value);
      return true;
    }

    function resetAlignment($element) {
      $element.removeClass('media-wysiwyg-align-' + currentAlignment)
        .removeAttr('data-picture-align')
        .css('float', '')
        .removeAttr('float');
    }

    function setAlignment($element, value) {
      var fid;
      var file_info;
      var delta;

      $element.addClass('media-wysiwyg-align-' + value);
      Drupal.media.filter.ensureDataMap();
      fid = $element.data('fid');
      if (fid && (file_info = Drupal.settings.mediaDataMap[fid])) {
        Drupal.settings.mediaDataMap[fid].fields.alignment = value;
        if ((delta = $element.data('delta'))) {
          Drupal.settings.mediaDataMap[fid].field_deltas[delta].alignment = value;
        }
      }
    }
  },

  /**
   * Get current alignment for element or null if not set.
   *
   * @param {jQuery} element
   *   The jQuery media element to get alignment from.
   *
   * @return {string}
   *   The current alignment.
   */
  getMediaAlignment: function ($element) {
    // First priority has media native alignment classes.
    var alignRe = /(?:.*\s+)?media-wysiwyg-align-(right|left|center)(?:s+.*)?/;
    var align = null;
    if ((align = $element.attr('class').match(alignRe))) {
      return align[1];
    }
    var tagName = $element[0].tagName.toLowerCase();
    if (tagName == 'img' || tagName == 'div') {
      align = $element.css('float');
      if (align == 'left' || align == 'right') {
        return align;
      }
      align = $element.attr('align');
      if (align == 'left' || align == 'right') {
        return align;
      }
    }
    return null;
  }

};

})(jQuery);
