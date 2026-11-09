"""Compare existing key-controlled game decisions with a pre-touch ELF."""
import argparse,hashlib,json
from pathlib import Path
from test_control_flow import ROOT,city_cases,number_cases,list_cases,battle_input_cases
from test_control_flow import run_city_selection,run_number_selection,run_list_selection,run_battle_input

def battle_decisions(result):
    value,trace,state,pending=result
    # The old blink counter read an uninitialized register. New input initializes
    # it; compare decisions/state/input exactly, with paint-only phase excluded.
    paint={'sango_battle_draw_units','sango_battle_scroll_viewport','sango_battle_draw_cursor',
           'sango_battle_draw_target_markers','sango_battle_draw_move_range'}
    return value,[row for row in trace if row[0] not in paint],state,pending

def main():
    p=argparse.ArgumentParser();p.add_argument('--baseline',type=Path,required=True);args=p.parse_args()
    before=args.baseline.read_bytes();after=(ROOT/'build/sango.elf').read_bytes();groups={}
    for name,cases,run in [('strategy',city_cases,run_city_selection),('number',number_cases,run_number_selection),('rosters',list_cases,run_list_selection),('battle',battle_input_cases,run_battle_input)]:
        count=0
        for case in cases():
            a,b=run(before,*case),run(after,*case)
            if name=='battle':a,b=battle_decisions(a),battle_decisions(b)
            if a!=b:
                raise AssertionError({'group':name,'case':repr(case),'return_equal':a[0]==b[0],
                                      'scope':'Exact state/results/input; old undefined blink paint excluded'})
            count+=1
        groups[name]=count;print(name,count,'passed',flush=True)
    report={'passed':sum(groups.values()),'failed':0,'groups':groups,
            'baseline_elf_sha256':hashlib.sha256(before).hexdigest(),
            'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'scope':'Actual compiled MIPS comparison with pre-touch ELF: exact strategy, decimal and roster return/state/input/render boundaries; battle decisions, legacy state and input consumption match, excluding paint-only phase/count from the old uninitialized cursor blink counter. New touch-only behavior is separately tested. Modeled SDK boundaries; not firmware or complete campaign.'}
    (ROOT/'build/touch-keyboard-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report))
if __name__=='__main__':main()
