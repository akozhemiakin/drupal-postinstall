<?php

/**
 * @file
 * Forms for the Postinstall module
 */

/**
 * Menu callback; display postinstall modules configure form.
 *
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 */
function postinstall_form($form, &$form_state) {
  // For the first time form is loaded get list of modules that need to be configured
  if (!isset($form_state['modules_to_configure'])) {
    $form_state['modules_to_configure'] = variable_get('postinstall_modules_to_configure', array());
    $form_state['steps_total'] = count($form_state['modules_to_configure']);
    if (count($form_state['modules_to_configure']) == 0) {
      variable_set('postinstall_modules_to_configure', array());
      drupal_goto('admin/modules');
    }
  }
  // For the first time form is loaded get first module from the stack to be configured
  if (!isset($form_state['current_module'])) {
    $form_state['current_module'] = array_shift($form_state['modules_to_configure']);
  }

  // Set up title
  $module_info = system_get_info('module', $form_state['current_module']);
  $current_step = $form_state['steps_total'] - count($form_state['modules_to_configure']);
  $title = t('Postinstall (Step !current_step of !steps_total): "!module_name" module', array(
    '!current_step' => $current_step,
    '!steps_total' => $form_state['steps_total'],
    '!module_name' => $module_info['name']
  ));
  drupal_set_title($title);

  $form['module'] = array(
    '#tree' => TRUE
  );
  $form['module'] += module_invoke($form_state['current_module'], 'postinstall', 'form');
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $form_state['steps_total'] == $current_step ? t('Finish') : t('Proceed')
  );

  return $form;
}

/**
 * Validate callback; handles postinstall form validation.
 */
function postinstall_form_validate($form, &$form_state) {
  $error_messages = (array)module_invoke($form_state['current_module'], 'postinstall', 'validate', $form_state['values']['module']);
  foreach ($error_messages as $message) {
    form_set_error('module][' . $message['name'], $message['message']);
  }
}

/**
 * Submit callback; handles postinstall form submission.
 */
function postinstall_form_submit($form, &$form_state) {
  module_invoke($form_state['current_module'], 'postinstall', 'submit', $form_state['values']['module']);

  if (count($form_state['modules_to_configure']) > 0) {
    $form_state['rebuild'] = TRUE;
    $form_state['current_module'] = array_shift($form_state['modules_to_configure']);
    variable_set('postinstall_modules_to_configure', $form_state['modules_to_configure']);

  }
  else {
    $form_state['rebuild'] = FALSE;
    $form_state['redirect'] = 'admin/modules';
    variable_set('postinstall_modules_to_configure', array());
  }
}

