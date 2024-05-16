# System-Bank-v1
<p style="-webkit-text-stroke-width:0px;background-color:rgb(25, 27, 28);color:rgb(232, 229, 225);font-family:-apple-system, Roboto, SegoeUI, &quot;Segoe UI&quot;, &quot;Helvetica Neue&quot;, Helvetica, &quot;Microsoft YaHei&quot;, &quot;Meiryo UI&quot;, Meiryo, &quot;Arial Unicode MS&quot;, sans-serif;font-size:16px;font-style:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variation-settings:var(--cib-type-body2-font-variation-settings);font-weight:400;letter-spacing:normal;line-height:var(--cib-type-body2-line-height);margin:0px !important 0px 0px;orphans:2;padding:0px;text-align:start;text-decoration-color:initial;text-decoration-style:initial;text-decoration-thickness:initial;text-indent:0px;text-transform:none;white-space:normal;widows:2;word-break:break-word;word-spacing:0px;">This system appears to be a basic bank management application implemented in C++. Here are the key components and functionalities:</p>
<ol style="-webkit-text-stroke-width:0px;background-color:rgb(25, 27, 28);color:rgb(232, 229, 225);display:flex;flex-direction:column;font-family:-apple-system, Roboto, SegoeUI, &quot;Segoe UI&quot;, &quot;Helvetica Neue&quot;, Helvetica, &quot;Microsoft YaHei&quot;, &quot;Meiryo UI&quot;, Meiryo, &quot;Arial Unicode MS&quot;, sans-serif;font-size:16px;font-style:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-weight:400;gap:4px;letter-spacing:normal;margin-bottom:0px;margin-right:0px;margin-top:12px;orphans:2;padding-inline-start:24px;text-align:start;text-decoration-color:initial;text-decoration-style:initial;text-decoration-thickness:initial;text-indent:0px;text-transform:none;white-space:normal;widows:2;word-spacing:0px;">
    <li>
        <p style="display:inline;font-size:var(--cib-type-body2-font-size);font-variation-settings:var(--cib-type-body2-font-variation-settings);font-weight:var(--cib-type-body2-font-weight);line-height:var(--cib-type-body2-line-height);margin:0px;padding:0px;word-break:break-word;"><strong style="font-size:var(--cib-type-subtitle2-stronger-font-size);font-variation-settings:var(--cib-type-subtitle2-stronger-font-variation-settings);font-weight:var(--cib-type-subtitle2-stronger-font-weight);line-height:var(--cib-type-subtitle2-stronger-line-height);">Struct </strong><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;"><strong style="font-size:var(--cib-type-subtitle2-stronger-font-size);font-variation-settings:var(--cib-type-subtitle2-stronger-font-variation-settings);font-weight:var(--cib-type-subtitle2-stronger-font-weight);line-height:var(--cib-type-subtitle2-stronger-line-height);">stInfoClient</strong></code>:</p>
        <ul style="display:flex;flex-direction:column;gap:4px;margin-bottom:0px;margin-right:0px;margin-top:12px;padding-inline-start:24px;">
            <li>
                <p style="margin-left:0px;">Represents client information, including account number, PIN code, client name, phone, balance, and a flag for deletion.</p>
            </li>
            <li>
                <p style="margin-left:0px;">Each client’s data is stored in an instance of this struct.</p>
            </li>
        </ul>
    </li>
    <li>
        <p style="display:inline;font-size:var(--cib-type-body2-font-size);font-variation-settings:var(--cib-type-body2-font-variation-settings);font-weight:var(--cib-type-body2-font-weight);line-height:var(--cib-type-body2-line-height);margin:0px;padding:0px;word-break:break-word;"><strong style="font-size:var(--cib-type-subtitle2-stronger-font-size);font-variation-settings:var(--cib-type-subtitle2-stronger-font-variation-settings);font-weight:var(--cib-type-subtitle2-stronger-font-weight);line-height:var(--cib-type-subtitle2-stronger-line-height);">Functions and Procedures</strong>:</p>
        <ul style="display:flex;flex-direction:column;gap:4px;margin-bottom:0px;margin-right:0px;margin-top:12px;padding-inline-start:24px;">
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">Backup()</code>: Displays a message and waits for a key press to return to the main menu.</p>
            </li>
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">PrintMainMenueScreen()</code>: Prints the main menu options.</p>
            </li>
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">PrintClient(stInfoClient client)</code>: Displays details of a single client.</p>
            </li>
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">PrintInfoLineClient(stInfoClient client)</code>: Prints a formatted line of client information.</p>
            </li>
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">PrintAllInfoClients(vector&lt;stInfoClient&gt;&amp; vClient)</code>: Prints a table of all clients’ information.</p>
            </li>
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">EndProgram()</code>: Displays a program-ending message and waits for a key press.</p>
            </li>
        </ul>
    </li>
    <li>
        <p style="display:inline;font-size:var(--cib-type-body2-font-size);font-variation-settings:var(--cib-type-body2-font-variation-settings);font-weight:var(--cib-type-body2-font-weight);line-height:var(--cib-type-body2-line-height);margin:0px;padding:0px;word-break:break-word;"><strong style="font-size:var(--cib-type-subtitle2-stronger-font-size);font-variation-settings:var(--cib-type-subtitle2-stronger-font-variation-settings);font-weight:var(--cib-type-subtitle2-stronger-font-weight);line-height:var(--cib-type-subtitle2-stronger-line-height);">Enum </strong><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;"><strong style="font-size:var(--cib-type-subtitle2-stronger-font-size);font-variation-settings:var(--cib-type-subtitle2-stronger-font-variation-settings);font-weight:var(--cib-type-subtitle2-stronger-font-weight);line-height:var(--cib-type-subtitle2-stronger-line-height);">enChoose</strong></code>:</p>
        <ul style="display:flex;flex-direction:column;gap:4px;margin-bottom:0px;margin-right:0px;margin-top:12px;padding-inline-start:24px;">
            <li>
                <p style="margin-left:0px;">Represents menu options (e.g., show client list, add new client, etc.).</p>
            </li>
        </ul>
    </li>
    <li>
        <p style="display:inline;font-size:var(--cib-type-body2-font-size);font-variation-settings:var(--cib-type-body2-font-variation-settings);font-weight:var(--cib-type-body2-font-weight);line-height:var(--cib-type-body2-line-height);margin:0px;padding:0px;word-break:break-word;"><strong style="font-size:var(--cib-type-subtitle2-stronger-font-size);font-variation-settings:var(--cib-type-subtitle2-stronger-font-variation-settings);font-weight:var(--cib-type-subtitle2-stronger-font-weight);line-height:var(--cib-type-subtitle2-stronger-line-height);">Data Handling Functions</strong>:</p>
        <ul style="display:flex;flex-direction:column;gap:4px;margin-bottom:0px;margin-right:0px;margin-top:12px;padding-inline-start:24px;">
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">SplitString(string S1, string Delim = "#//#")</code>: Splits a string into a vector of substrings using a delimiter.</p>
            </li>
            <li>
                <p style="margin-left:0px;"><code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">ConvertLineToRecord(string S1, string Seperator = "#//#")</code>: Converts a line of data (from a file) into a <code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">stInfoClient</code> record.</p>
            </li>
        </ul>
    </li>
    <li>
        <p style="display:inline;font-size:var(--cib-type-body2-font-size);font-variation-settings:var(--cib-type-body2-font-variation-settings);font-weight:var(--cib-type-body2-font-weight);line-height:var(--cib-type-body2-line-height);margin:0px;padding:0px;word-break:break-word;"><strong style="font-size:var(--cib-type-subtitle2-stronger-font-size);font-variation-settings:var(--cib-type-subtitle2-stronger-font-variation-settings);font-weight:var(--cib-type-subtitle2-stronger-font-weight);line-height:var(--cib-type-subtitle2-stronger-line-height);">Usage</strong>:</p>
        <ul style="display:flex;flex-direction:column;gap:4px;margin-bottom:0px;margin-right:0px;margin-top:12px;padding-inline-start:24px;">
            <li>
                <p style="margin-left:0px;">The program likely reads data from a file (e.g., “MyFill.text”) to populate the <code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">stInfoClient</code> structs.</p>
            </li>
            <li>
                <p style="margin-left:0px;">It provides menu options for managing clients (showing, adding, updating, deleting, finding).</p>
            </li>
            <li>
                <p style="margin-left:0px;">The <code style="border-radius:var(--cib-border-radius-medium);border:1px solid var(--darkreader-border--cib-color-stroke-neutral-primary);box-sizing:border-box;font-size:var(--cib-type-body1-font-size);font-variation-settings:var(--cib-type-body1-font-variation-settings);font-weight:500;line-height:var(--cib-type-body1-line-height);margin:0px 2px;padding:1px 4px;white-space:pre-wrap;">PrintAllInfoClients</code> function displays a table of client information.</p>
            </li>
        </ul>
    </li>
</ol>
