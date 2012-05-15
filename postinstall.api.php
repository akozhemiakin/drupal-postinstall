<?php

/**
 * @file
 * Hooks provided by Postinstall module.
 */

/**
 * This hook allow modules to display and handle postinstall configuration
 * forms.
 * 
 * @param $action
 *   One of those three values:
 *   - form: Return normal form array as you do it in drupal_get_form(). You 
 *     should not provide any submit form elements here.
 *   - validate: Here you coul check $values provided by user and return 
 *     $error_messages if any. $error_messages is an array with following keys:
 *     - name: The name of the form element (as in form_set_error()).
 *     - message: The error message to present to the user.
 *   - submit: Submit callback of your form. Here you can do something with
 *     $values.
 * @param $values
 *   Values to be validated (when $action == 'validate') or submited (when
 *   $action == 'submit').
 */
function hook_postinstall($action, $values = array()) {
  switch ($action) {
    case 'form':
      $form = array();
      $form['test'] = array(
        '#type' => 'textfield',
        '#title' => 'Test textfield'
      );
      return $form;
      break;
    case 'validate':
      $error_messages = array();
      if (!is_numeric($values['test'])) {
        $error_messages[] = array(
          'name' => 'test',
          'message' => t('Translated message')
        );
      }
      return $error_messages;
      break;
    case 'submit':
      drupal_set_message($values['test']);
      break;
  }
}
